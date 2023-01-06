//
//  CAEAGLView.m
//  NKVideoEditing
//
//  Created by niekang on 2022/9/8.
//

#import "CAEAGLView.h"
#import <OpenGLES/ES2/gl.h>

enum VertexAttribType {
    VertexAttribTypePosition,
    VertexAttribTypeTexture
};

static const GLfloat imageVertices[] = {
    -1, -1,
    -1, 1,
    1, 1,
    1, -1
};

static const GLfloat textureCordinates[] = {
    0,0,
    0,1,
    1,0,
    1,1
};

@interface CAEAGLView () {
    EAGLContext *_context;
    CAEAGLLayer *_glLayer;
    GLuint _frameBuffer;
    GLuint _renderBuffer;
    GLuint _program;
    GLint _renderBufferWidth;
    GLint _renderBufferHeight;
}

@end

@implementation CAEAGLView

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        [self initConfiguration];
    }
    return self;
}

- (void)initConfiguration {
    _glLayer = (CAEAGLLayer *)self.layer;
    _glLayer.contentsScale = UIScreen.mainScreen.scale;
    _glLayer.opaque = YES;
    _glLayer.drawableProperties = @{kEAGLDrawablePropertyRetainedBacking: @(NO)};
    
    _context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    
    [self initGLConfigration];
}

- (void)initGLConfigration {
    if (!_context || ![EAGLContext setCurrentContext:_context]) {
        return;
    }
    
    // 设置缓冲
    [self initBuffers];
    
    // 加载着色器
    [self initShaders];
    
    // 使用程序
    glUseProgram(_program);
}

- (void)initBuffers {
    // 深度测试的目的是为了绘制当前像素组中里屏幕最近的像素。
    glDisable(GL_DEPTH_TEST);
    
    glEnableVertexAttribArray(VertexAttribTypePosition);
    glVertexAttribPointer(VertexAttribTypePosition, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 2, NULL);
    
    glEnableVertexAttribArray(VertexAttribTypeTexture);
    glVertexAttribPointer(VertexAttribTypeTexture, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 2, NULL);
    
    glGenFramebuffers(1, &_frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
    
    glGenRenderbuffers(1, &_renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _renderBuffer);
    
    // 绑定渲染缓存区, 不先绑定会影响 glCheckFramebufferStatus结果
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_glLayer];
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _renderBuffer);
        
    // 检查帧缓冲区状态
    GLenum bufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (bufferStatus != GL_FRAMEBUFFER_COMPLETE) {
        NSLog(@"failed to make frame buffer: %x",bufferStatus);
    }

    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &_renderBufferWidth);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &_renderBufferHeight);
}

- (void)initShaders {
    _program = glCreateProgram();
    
    const char *vertexShaderStr = [[NSString alloc] initWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"shader" ofType:@"vsh"] encoding:NSUTF8StringEncoding error:NULL].UTF8String;
    
    const char *fragShaderStr = [[NSString alloc] initWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"shader" ofType:@"fsh"] encoding:NSUTF8StringEncoding error:NULL].UTF8String;

    GLuint vertexShader, fraShader;
    [self compileShader:&vertexShader shaderString:vertexShaderStr type:GL_VERTEX_SHADER];
    [self compileShader:&fraShader shaderString:fragShaderStr type:GL_FRAGMENT_SHADER];
    
    glAttachShader(_program, vertexShader);
    glAttachShader(_program, fraShader);
    
#if DEBUG
    GLint logLength;
    glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(_program, logLength, &logLength, log);
        NSLog(@"Program link log:\n%s", log);
        free(log);
    }
#endif

    GLint status;
    glLinkProgram(_program);
    
    glGetProgramiv(_program, GL_LINK_STATUS, &status);
    if (status == 0) {
        NSLog(@"program link failed: %x", status);
    }
}

- (BOOL)compileShader:(GLuint *)shader shaderString:(const char *)shaderString type:(GLenum)type {
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &shaderString, NULL);
    glCompileShader(*shader);
#if DEBUG
    GLint logLength;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(*shader, logLength, &logLength, log);
        NSLog(@"%x shader compile log:\n%s",type, log);
        free(log);
    }
#endif
    
    GLint status;
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        glDeleteShader(*shader);
        return NO;
    }
    return YES;
}

+ (Class)layerClass {
    return [CAEAGLLayer class];
}

@end
