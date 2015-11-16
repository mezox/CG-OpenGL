#include "OBJModel.h"

#include "Strings.h"
#include <fstream>

#ifdef _MSC_VER
#	define FORCE_INLINE __forceinline
#	define FLATTEN 
#elif defined(__GNUC__) && __GNUC__ > 4
#	define FORCE_INLINE __attribute__((always_inline))
#	define FLATTEN __attribute__((flatten))
#endif

namespace Forest
{
	namespace Graphics
	{
		//Struct holding data about one triangle
		struct Triangle
		{
			uint32_t v[3];
			uint32_t t[3];
			uint32_t n[3];
		};

		class ObjLexer
		{
		public:
			enum Tokens
			{
				T_Eof = 0,
				T_Face = 'f' << 8 | ' ',
				T_Face2 = 'f' << 8 | '\t',
				T_Vertex = 'v' << 8 | ' ',
				T_Vertex2 = 'v' << 8 | '\t',
				T_Normal = 'v' << 8 | 'n',
				T_TexCoord = 'v' << 8 | 't',
			};

		public:
			ObjLexer(istream* input) :
				m_Input(input),
				m_BufferPos(0),
				m_BufferEnd(0)
			{ }

			FORCE_INLINE int FillBuffer()
			{
				if (m_BufferPos >= m_BufferEnd)
				{
					m_Input->read(m_Buffer, BUFFER_SIZE);
					m_BufferEnd = int(m_Input->gcount());
					m_BufferPos = 0;
				}

				return m_BufferEnd != 0;
			}

			FORCE_INLINE int NextChar()
			{
				if (FillBuffer())
					return m_Buffer[m_BufferPos++];
				
				return 0;
			}

			int FirstLine()
			{
				return NextChar() << 8 | NextChar();
			}

			FORCE_INLINE int NextLine()
			{
				// scan to end of line...
				while ('\n' != NextChar()) {}
				while (MatchChar('\n') || MatchChar('\r')) {}
				
				// Or: convert next 2 chars to token (16 bit), can be mt, us, vn, vt, v , v\t, f , f\t, unknown
				return NextChar() << 8 | NextChar();
			}


			FORCE_INLINE bool Match(const char s[], const size_t l)
			{
				for (int i = 0; FillBuffer() && i < int(l) - 1; ++i)
					if (s[i] != m_Buffer[m_BufferPos])
						return false;
					else
						++m_BufferPos;
				
				return true;
			}


			FORCE_INLINE bool MatchString(ustring &str)
			{
				while (FillBuffer() && !isspace(m_Buffer[m_BufferPos]))
					str.push_back(m_Buffer[m_BufferPos++]);

				return !str.empty();
			}


			FORCE_INLINE bool MatchFloat(float &result)
			{
				bool found = false;
				result = 0.0f;
				float sign = 1.0f;

				if (MatchChar('-'))
				{
					sign = -1.0f;
					found = true;
				}

				char c;
				
				while (FillBuffer() && MyIsDigit(c = m_Buffer[m_BufferPos]))
				{
					result = result * 10.0f + float(c - '0');
					++m_BufferPos;
					found = true;
				}

				float frac = 0.1f;
				
				if (MatchChar('.'))
				{
					char c;
					while (FillBuffer() && MyIsDigit(c = m_Buffer[m_BufferPos]))
					{
						result += frac * float(c - '0');
						++m_BufferPos;
						frac *= 0.1f;
					}

					found = true;
				}

				if (MatchChar('e') || MatchChar('E'))
				{
					float expSign = MatchChar('-') ? -1.0f : 1.0f;
					
					uint32_t exp = 0;
					
					if (MatchInt(exp))
						result = result * powf(10.0f, float(exp) * expSign);
				}

				result *= sign;
				
				return found;
			}


			FORCE_INLINE bool MyIsDigit(char c)
			{
				return ((unsigned int)(c)-(unsigned int)('0') < 10U);
			}


			FORCE_INLINE bool MatchInt(uint32_t &result)
			{
				bool found = false;
				result = 0;
				char c;
				while (FillBuffer() && MyIsDigit(c = m_Buffer[m_BufferPos]))
				{
					result = result * 10 + int(c - '0');
					++m_BufferPos;
					found = true;
				}

				return found;
			}


			FORCE_INLINE bool MatchChar(int MatchTo)
			{
				if (FillBuffer() && m_Buffer[m_BufferPos] == MatchTo)
				{
					m_BufferPos++;
					return true;
				}
				return false;
			}


			FORCE_INLINE bool MatchWs(bool optional = false)
			{
				bool found = false;

				while (FillBuffer() && (m_Buffer[m_BufferPos] == ' ' || m_Buffer[m_BufferPos] == '\t'))
				{
					found = true;
					m_BufferPos++;
				}

				return found || optional;
			}

		private:
			istream*	m_Input;
			char		m_Buffer[BUFFER_SIZE];
			int			m_BufferPos;
			int			m_BufferEnd;
		};



		FORCE_INLINE static bool ParseFaceIndSet(ObjLexer &lexer, Triangle &t, uint32_t v)
		{
			t.v[v] = -1;
			t.t[v] = -1;
			t.n[v] = -1;

			if (lexer.MatchWs(true)	&& lexer.MatchInt(t.v[v]) && lexer.MatchChar('/')
				&& (lexer.MatchInt(t.t[v]) || true)  // The middle index is optional!
				&& lexer.MatchChar('/')
				&& lexer.MatchInt(t.n[v]))
			{
				// need to adjust for silly obj 1 based indexing
				t.v[v] -= 1;
				t.t[v] -= 1;
				t.n[v] -= 1;
				
				return true;
			}

			return false;
		}


		const ustring OBJModel::MODELS_DIR = U("Models/");
		const ustring OBJModel::TEXTURES_DIR = U("Textures/");

		OBJModel::OBJModel(const ustring& file, bool hasTextures, bool hasTransparency) :
			m_FileName(file),
			m_VerticesCnt(0),
			m_IndicesCnt(0),
			m_ShineDamper(5.0f),
			m_Reflectivity(0.0f),
			m_bHasTextures(hasTextures),
			m_bHasTransparency(hasTransparency),
			m_bUseFakeLighting(false)
		{
			if (hasTextures)
			{
				m_DiffuseTex = new Texture();
				m_DiffuseTex->Load(TEXTURES_DIR + m_FileName + U(".jpg"));
			}
			else
				m_DiffuseTex = nullptr;

			if (hasTransparency)
			{
				m_AlphaTex = new Texture();
				m_AlphaTex->Load(TEXTURES_DIR + m_FileName + U("_alpha.jpg"));
			}
			else
				m_AlphaTex = nullptr;
		}

		OBJModel::~OBJModel()
		{
			glDeleteBuffers(1, &m_PositionsVBO);
			glDeleteBuffers(1, &m_UVsVBO);
			glDeleteBuffers(1, &m_NormalsVBO);
			glDeleteBuffers(1, &m_IndicesVBO);
			glDeleteVertexArrays(1, &m_Vao);

			if (HasTextures())
			{
				m_DiffuseTex->Unbind();
				delete m_DiffuseTex;
				m_DiffuseTex = nullptr;
			}

			if (HasTransparency())
			{
				m_AlphaTex->Unbind();
				delete m_AlphaTex;
				m_AlphaTex = nullptr;
			}
		}


		bool FLATTEN OBJModel::LoadOBJ(bool bExportBinary)
		{
			ifstream file;

			file.open((MODELS_DIR + m_FileName + U(".obj")).c_str(), std::ios::binary);

			if (!file)
			{
				ucout << U("Error while opening file: ") << m_FileName <<  endl;
				return false;
			}

			ucout << U("Loading OBJ file: ") << m_FileName << std::endl;

			vector<Vector2> uvs;
			vector<Vector3> normals;
			vector<Triangle> faces;

			m_Positions.reserve(256 * 1024);
			normals.reserve(256 * 1024);
			uvs.reserve(256 * 1024);
			faces.reserve(256 * 1024);

			ObjLexer lexer(&file);

			for (int token = lexer.FirstLine(); token != ObjLexer::T_Eof; token = lexer.NextLine())
			{
				switch (token)
				{
					case ObjLexer::T_Vertex:
					case ObjLexer::T_Vertex2:
					{
						Vector3 p;
						if (lexer.MatchWs(true)	&& lexer.MatchFloat(p.x) && lexer.MatchWs() && 
							lexer.MatchFloat(p.y) && lexer.MatchWs() && lexer.MatchFloat(p.z))
							m_Positions.push_back(p);
					}
					break;

					case ObjLexer::T_Normal:
					{
						Vector3 n;
						if (lexer.MatchWs(true)	&& lexer.MatchFloat(n.x) && lexer.MatchWs()	&&
							lexer.MatchFloat(n.y) && lexer.MatchWs() && lexer.MatchFloat(n.z))
							normals.push_back(n);
					}
					break;
					
					case ObjLexer::T_TexCoord:
					{
						Vector2 t;
						if (lexer.MatchWs(true) && lexer.MatchFloat(t.x) &&
							lexer.MatchWs() && lexer.MatchFloat(t.y))
						{
							t.y = 1.0f - t.y;
							uvs.push_back(t);
						}
							
					}
					break;

					case ObjLexer::T_Face:
					case ObjLexer::T_Face2:
					{
						Triangle t;
						// parse vert 0 and 1
						if (ParseFaceIndSet(lexer, t, 0) && ParseFaceIndSet(lexer, t, 1))
						{
							// let any more produce one more triangle
							while (ParseFaceIndSet(lexer, t, 2))
							{
								faces.push_back(t);
								
								// the make last vert second (this also keeps winding the same).
								t.n[1] = t.n[2];
								t.t[1] = t.t[2];
								t.v[1] = t.v[2];
							}
						}
					}
					break;

					default:
						break;
					};
			}

			file.close();

			m_VerticesCnt = m_Positions.size();
			m_IndicesCnt = faces.size() * 3;

			m_TexCoords_elem.resize(m_VerticesCnt, Vector2());
			m_Normals_elem.resize(m_VerticesCnt, Vector3());

			//Sort
			for (size_t fidx = 0; fidx < faces.size(); fidx++)
			{
				Triangle tmp = faces[fidx];

				for (int vidx = 0; vidx < 3; vidx++)
				{
					uint32_t vp = tmp.v[vidx];
					Vector2 tc = uvs.at(tmp.t[vidx]);
					Vector3 vn = normals.at(tmp.n[vidx]);

					m_Indices.push_back(vp);

					m_TexCoords_elem[vp] = tc;
					m_Normals_elem[vp] = vn;
				}
			}

			//Export .OBJ to .COBJ
			if (bExportBinary)
				SaveBinary();

			StoreDataInVBO();
			
			return true;
		}


		void OBJModel::SaveBinary()
		{
			std::ofstream stream;
			stream.open((MODELS_DIR + m_FileName + U(".cobj")).c_str(), std::ios::binary);

			assert(sizeof(float) == sizeof(uint32_t));
			
			const auto sz = sizeof(uint32_t);

			const uint32_t nVertices = (uint32_t)m_Positions.size();
			const uint32_t nTexcoords = (uint32_t)m_TexCoords_elem.size();
			const uint32_t nNormals = (uint32_t)m_Normals_elem.size();
			const uint32_t nIndices = (uint32_t)m_Indices.size();

			ucout << "Writing to binary file:\n";
			ucout << "Vertices: " << nVertices << "\n";
			ucout << "TexCoords: " << nTexcoords << "\n";
			ucout << "Normals: " << nNormals << "\n";

			stream.write((const char*)&nVertices, sz);
			stream.write((const char*)&nTexcoords, sz);
			stream.write((const char*)&nNormals, sz);
			stream.write((const char*)&nIndices, sz);

			stream.write((const char*)&m_Positions[0], nVertices * 3 * sz);
			stream.write((const char*)&m_TexCoords_elem[0], nTexcoords * 2 * sz);
			stream.write((const char*)&m_Normals_elem[0], nNormals * 3 * sz);
			stream.write((const char*)&m_Indices[0], nIndices * sz);

			stream.close();
		}


		void OBJModel::LoadBinary()
		{
			ifstream file;
			file.open((MODELS_DIR + m_FileName + U(".cobj")).c_str(), std::ios::binary);

			if (!file)
			{
				ucout << U("Error while opening file: ") << m_FileName << endl;
				return;
			}

			ucout << U("Loading COBJ file: ") << m_FileName << std::endl;

			assert(sizeof(float) == sizeof(uint32_t));
			const auto sz = sizeof(uint32_t);

			uint32_t nVertices = 0, nNormals = 0, nTexcoords = 0, nIndices = 0;
				
			file.read((char*)&nVertices, sz);
			file.read((char*)&nNormals, sz);
			file.read((char*)&nTexcoords, sz);
			file.read((char*)&nIndices, sz);

			m_VerticesCnt = nVertices;
			m_IndicesCnt = nIndices;

			ucout << "Vertices: " << nVertices << "\n";
			ucout << "TexCoords: " << nTexcoords << "\n";
			ucout << "Normals: " << nNormals << "\n";

			m_Positions.resize(nVertices);
			m_Normals_elem.resize(nNormals);
			m_TexCoords_elem.resize(nTexcoords);
			m_Indices.resize(nIndices);

			file.read((char*)&m_Positions[0], nVertices * 3 * sz);
			file.read((char*)&m_TexCoords_elem[0], nTexcoords * 2 * sz);
			file.read((char*)&m_Normals_elem[0], nNormals * 3 * sz);
			file.read((char*)&m_Indices[0], nIndices * sz);

			StoreDataInVBO();
		}


		/// <summary>
		/// Stores loaded model data in VBOs.
		/// </summary>
		void OBJModel::StoreDataInVBO()
		{
			glGenVertexArrays(1, &m_Vao);
			glBindVertexArray(m_Vao);
			glGenBuffers(1, &m_PositionsVBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_PositionsVBO);
			glBufferData(GL_ARRAY_BUFFER, m_VerticesCnt * sizeof(Vector3), &m_Positions[0].x, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glGenBuffers(1, &m_UVsVBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_UVsVBO);
			glBufferData(GL_ARRAY_BUFFER, m_TexCoords_elem.size() * sizeof(Vector2), &m_TexCoords_elem[0].x, GL_STATIC_DRAW);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glGenBuffers(1, &m_NormalsVBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_NormalsVBO);
			glBufferData(GL_ARRAY_BUFFER, m_Normals_elem.size() * sizeof(Vector3), &m_Normals_elem[0].x, GL_STATIC_DRAW);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glGenBuffers(1, &m_IndicesVBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndicesVBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndicesCnt * sizeof(uint32_t), &m_Indices[0], GL_STATIC_DRAW);

			DeleteCPUData();
		}


		/// <summary>
		/// Deletes vertex data from memory.
		/// </summary>
		void OBJModel::DeleteCPUData()
		{
			m_Positions.clear();
			m_TexCoords_elem.clear();
			m_Normals_elem.clear();
			m_Indices.clear();

			m_Positions.shrink_to_fit();
			m_TexCoords_elem.shrink_to_fit();
			m_Normals_elem.shrink_to_fit();
			m_Indices.shrink_to_fit();
		}
	}
}