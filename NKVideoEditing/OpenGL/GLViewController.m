//
//  GLViewController.m
//  NKVideoEditing
//
//  Created by niekang on 2022/9/6.
//

#import "GLViewController.h"
#import <GLKit/GLKit.h>
#import <OpenGLES/ES2/gl.h>
#import "CAEAGLView.h"

@interface GLViewController ()<GLKViewDelegate>

@property(nonatomic, strong)EAGLContext *glCtx;
@property(nonatomic, strong)GLKView *glView;
@property(nonatomic, strong)GLKBaseEffect *baseEffect;

@end

@implementation GLViewController

-(instancetype)initWithCoder:(NSCoder *)coder {
    self = [super initWithCoder:coder];
    if (self) {
        self.modalPresentationStyle = UIModalPresentationFullScreen;
    }
    return self;
}
- (void)viewDidLoad {
    [super viewDidLoad];
    
    CAEAGLView *view = [[CAEAGLView alloc] initWithFrame:CGRectMake(0, 30, self.view.frame.size.width, 200)];
    view.backgroundColor = UIColor.redColor;
    [self.view addSubview:view];
    // 初始化
//    [self renderWithGLKView];
}


- (void)renderWithGLKView {
    //    纹素（Texel）： 一个图像初始化为一个纹理缓存后，每个像素会变成一个纹素。纹理的坐标是范围是 0 ~ 1，在这个单位长度内，可能包含任意多个纹素。
    //    光栅化（Rasterizing）： 将几何形状数据转换为片段的渲染步骤。
    //    片段（Fragment）： 视口坐标中的颜色像素。没有使用纹理时，会使用对象顶点来计算片段的颜色；使用纹理时，会根据纹素来计算。
    //    映射（Mapping）： 对齐顶点和纹素的方式。即将顶点坐标 (X, Y, Z) 与 纹理坐标 (U, V) 对应起来。
    //    取样（Sampling）： 在顶点固定后，每个片段根据计算出来的 (U, V) 坐标，去找相应纹素的过程。
    //    帧缓存（Frame Buffer）： 一个接收渲染结果的缓冲区，为 GPU 指定存储渲染结果的区域。更通俗点，可以理解成存储屏幕上最终显示的一帧画面的区域。
    self.glCtx = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    // 加载纹理
    NSString *imagePath = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"girl.jpg"];
    UIImage *image = [UIImage imageWithContentsOfFile:imagePath];
    
    self.glView = [[GLKView alloc] initWithFrame:CGRectMake((self.view.frame.size.width-200)/2.f, 300, 200, 200 * image.size.height/image.size.width) context:self.glCtx];
    self.glView.delegate = self;
    [self.view addSubview:self.glView];
    
    [EAGLContext setCurrentContext:self.glView.context];

    NSDictionary *options = @{GLKTextureLoaderOriginBottomLeft:@(YES)};
    GLKTextureInfo *textureInfo = [GLKTextureLoader textureWithCGImage:image.CGImage options:options error:NULL];
    
    self.baseEffect = [[GLKBaseEffect alloc] init];
    self.baseEffect.texture2d0.name = textureInfo.name;
    self.baseEffect.texture2d0.target = textureInfo.target;
    
    [self.glView display];
}


#pragma makr - GLKViewDelegate
- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
//    glClear(GL_COLOR_BUFFER_BIT);
    [self.baseEffect prepareToDraw];
    
    float vertices[] = {
        -1, 1, 0, 0, 1, // 左上
        -1, -1, 0, 0, 0, // 左下
        1, 1, 0, 1, 1, // 右上
        1, -1, 0, 1, 0 // 右下
    };
    
    // 各个方法解释
    // https://learnopengl-cn.github.io/01%20Getting%20started/04%20Hello%20Triangle/
    
    GLuint vertextBuffer;
    // 创建定点缓存
    // 第一个参数是要生成的缓冲对象的数量，
    // 第二个是要输入用来存储缓冲对象名称的数组
    glGenBuffers(1, &vertextBuffer);
    
    // 绑定
    // 第一个就是缓冲对象的类型
    // 第二个参数就是要绑定的缓冲对象的名称，
    // 使用该函数将缓冲对象绑定到OpenGL上下文环境中以便使用,如果把target绑定到一个已经创建好的缓冲对象，那么这个缓冲对象将为当前target的激活对象；但是如果绑定的buffer值为0，那么OpenGL将不再对当前target使用任何缓存对象。
   
    glBindBuffer(GL_ARRAY_BUFFER, vertextBuffer);
    
    // 把数据复制到当前绑定缓冲的函数
    // 它的第一个参数是目标缓冲的类型
    // 第二个参数指定传输数据的大小(以字节为单位),用一个简单的sizeof计算出顶点数据大小就行
    // 第三个参数是我们希望发送的实际数据
    // 第四个参数指定了我们希望显卡如何管理给定的数据
    // GL_STATIC_DRAW ：数据不会或几乎不会改变。GL_DYNAMIC_DRAW：数据会被改变很多。GL_STREAM_DRAW ：数据每次绘制时都会改变。
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // 设置顶点属性指针
    // 允许使用顶点数据
    glEnableVertexAttribArray(GLKVertexAttribPosition);
    
    // 参数1: 指定要修改的属性的索引值
    // 参数2: 每次读取数量(如position是由3个（x,y,z）组成，而颜色是4个（r,g,b,a）,纹理则是2个.)
    // 参数3: 指定数组中每个组件的数据类型。可用的符号常量有GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_FIXED, 和 GL_FLOAT，初始值为GL_FLOAT。
    // 参数4: 指定当被访问时，固定点数据值是否应该被归一化（GL_TRUE）或者直接转换为固定点值（GL_FALSE）
    // 参数5: 指定连续顶点属性之间的偏移量。如果为0，那么顶点属性会被理解为：它们是紧密排列在一起的。初始值为0
    // 参数6: 指定一个指针，指向数组中第一个顶点属性的第一个组件。初始值为0
    glVertexAttribPointer(GLKVertexAttribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*5, (GLfloat *)NULL + 0);
    
    // 允许使用纹理数据
    glEnableVertexAttribArray(GLKVertexAttribTexCoord0);
    glVertexAttribPointer(GLKVertexAttribTexCoord0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*5, (GLfloat *)NULL + 3);
    
    // 绘制
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    // 删除缓存
    glDeleteBuffers(1, &vertextBuffer);
    vertextBuffer = 0;
}


@end
