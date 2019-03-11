ModelLoader  - model loader (at least .OBJ format support).

Uses the following libraries:
	GLEW, version 2.0.0 (http://glew.sourceforge.net/)
	GLFW, version 3.2.1 (http://www.glfw.org/)
	GLM, version 0.9.8.4 (http://glm.g-truc.net/)
	SOIL (http://www.lonesock.net/soil.html)

Created: March 11, 2019

////////////////////////////////////////

TODO:
1) the indices are wrong
2) move the VAO and buffers to the PMesh class and make the vertices, indices, etc. private
3) remove scaling of the model from PMesh::addVertex()
