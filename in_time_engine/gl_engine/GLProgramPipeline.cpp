#include "GLProgramPipeline.h"

// class GLSLProgramPipeline

// Object | public

// Constructor / Destructor
gl::ProgramPipeline::ProgramPipeline() {
	glCreateProgramPipelines(1, &id);
}
gl::ProgramPipeline::~ProgramPipeline() {
	glDeleteProgramPipelines(1, &id);
}

// Getters
unsigned int gl::ProgramPipeline::getId() const {
	return id;
}

// Functions
void gl::ProgramPipeline::useProgramStages(unsigned int shaderType, unsigned int programId) const {
	glUseProgramStages(id, shaderType, programId);
}
void gl::ProgramPipeline::useProgramStages(gl::ShaderType shaderType, const gl::Program& program) const {
	glUseProgramStages(id, (unsigned int)shaderType, program.getId());
}
void gl::ProgramPipeline::bind() const {
	glUseProgram(0); // Unbind any program currently in use to enable pipeline use
	glBindProgramPipeline(id);
}
