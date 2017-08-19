#include "program_gl.h"
#include "log\log.h"
#include "allocator\allocator.h"

namespace WingRendererGL
{

	void printShaderInfoLog(GLuint obj)
	{
		int infologLength = 0;
		int charsWritten = 0;
		char *infoLog;

		glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

		if (infologLength > 1)
		{
			infoLog = (char *)WING_ALLOC(infologLength);
			glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
			WING_LOG_ERROR(infoLog);
			WING_FREE(infoLog);
		}
	}


	void printProgramInfoLog(GLuint obj)
	{
		int infologLength = 0;
		int charsWritten = 0;
		char *infoLog;

		glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

		if (infologLength > 1)
		{
			infoLog = (char *)WING_ALLOC(infologLength);
			glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
			WING_LOG_ERROR(infoLog);
			WING_FREE(infoLog);
		}
	}


	ProgramGL::ProgramGL()
	{

	}
	ProgramGL::~ProgramGL()
	{

	}

	void ProgramGL::create(std::string vs, std::string fs)
	{
		const char *vv = vs.c_str();
		const char *ff = fs.c_str();

		GLint _vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(_vs, 1, &vv, NULL);
		glCompileShader(_vs);
		printShaderInfoLog(_vs);


		GLint _fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(_fs, 1, &ff, NULL);
		glCompileShader(_fs);
		printShaderInfoLog(_fs);

		mProgramID = glCreateProgram();

		glAttachShader(mProgramID, _vs);
		glAttachShader(mProgramID, _fs);

		glLinkProgram(mProgramID);
		printProgramInfoLog(mProgramID);

		glDeleteShader(_vs);
		glDeleteShader(_fs);
	}


	void ProgramGL::use()
	{
		if (mProgramID != INVALID_PROGRAM)
		{
			glUseProgram(mProgramID);
		}
	}

	void ProgramGL::destroy()
	{
		if (mProgramID != INVALID_PROGRAM)
		{
			glDeleteProgram(mProgramID);
		}
	}
}