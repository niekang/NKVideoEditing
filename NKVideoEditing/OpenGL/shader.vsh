attribute vec4 position;
attribute vec2 textureCoordinate;

varying vec2 outTextureCoordinate;
void main() {
    gl_Position = position;
    outTextureCoordinate = textureCoordinate;
}


