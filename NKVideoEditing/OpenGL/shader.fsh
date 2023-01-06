varying highp vec2 outTextureCoordinate;
uniform sampler2D smaplerRGBA;

void main() {
    //https://zhuanlan.zhihu.com/p/103688218
    gl_FragColor = texture2D(smaplerRGBA, outTextureCoordinate);
}
