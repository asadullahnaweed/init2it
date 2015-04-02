/*========================================================================
  VES --- VTK OpenGL ES Rendering Toolkit

      http://www.kitware.com/ves

  Copyright 2011 Kitware, Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
 ========================================================================*/
#import "MyGLKViewController.h"
#import "MyGestureHandler.h"

#include "AsadKiwiApp.h"


@interface MyGLKViewController () {

  AsadKiwiApp::Ptr mKiwiApp;

  MyGestureHandler* mGestureHandler;
    NSTimer * animationTimer;
}

@property (strong, nonatomic) EAGLContext *context;

- (void)tearDownGL;
- (void)onTimer;

@end

@implementation MyGLKViewController

- (void)viewDidLoad {
  [super viewDidLoad];

  self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

  if (!self.context) {
      NSLog(@"Failed to create ES context");
  }

  GLKView *view = (GLKView *)self.view;
  view.context = self.context;
  view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
  view.drawableMultisample = GLKViewDrawableMultisample4X;

  [self initializeKiwiApp];
  [self initializeGestureHandler];
    animationTimer = [NSTimer scheduledTimerWithTimeInterval:0.01 target:self selector:@selector(onTimer) userInfo:nil repeats:YES];
}

-(void) initializeKiwiApp
{
  [EAGLContext setCurrentContext:self.context];
    NSLog(@"Sprinkle 0");
    NSString* resName = [[NSBundle mainBundle] pathForResource:@"headslices" ofType:@"vti"];
    if (resName == nil) {
        NSLog(@"The resource could not be loaded!");
    }
    else {
        NSLog(@"%@", resName);
    }
  std::string dataset = [resName UTF8String];

  self->mKiwiApp = AsadKiwiApp::Ptr(new AsadKiwiApp);
  self->mKiwiApp->initGL();
  [self resizeView];
    NSLog(@"Sprinkle 1");
    if (!self->mKiwiApp->loadDataset(dataset)) {
        NSLog(@"The dataset could not be loaded!");
    }
    NSLog(@"Sprinkle 2");
  self->mKiwiApp->loadText();
  self->mKiwiApp->resetView();
}

-(void) initializeGestureHandler {
  self->mGestureHandler = [[MyGestureHandler alloc] init];
  self->mGestureHandler.view = self.view;
  self->mGestureHandler.kiwiApp = self->mKiwiApp;
  [self->mGestureHandler createGestureRecognizers];
}

-(void) onTimer {
    mKiwiApp->animationStep();
}

- (void)dealloc {
  [self tearDownGL];

  if ([EAGLContext currentContext] == self.context) {
      [EAGLContext setCurrentContext:nil];
  }
}

- (IBAction)onSwitchPress:(UISwitch *)sender {
    if ([sender isOn]) {
        mKiwiApp->setMeasureMode(true);
    }
    else {
        mKiwiApp->setMeasureMode(false);
    }
}


- (void)didReceiveMemoryWarning
{
  [super didReceiveMemoryWarning];

  if ([self isViewLoaded] && ([[self view] window] == nil)) {
    self.view = nil;

    [self tearDownGL];

    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
    self.context = nil;
  }

  // Dispose of any resources that can be recreated.
}

- (void)tearDownGL
{
  [EAGLContext setCurrentContext:self.context];

  // free GL resources
  // ...
}

-(void) resizeView
{
  double scale = self.view.contentScaleFactor;
  self->mKiwiApp->resizeView(self.view.bounds.size.width*scale, self.view.bounds.size.height*scale);
}

- (void)viewWillLayoutSubviews
{
  [self resizeView];
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
  if (self->mKiwiApp && !self.paused) {
      self->mKiwiApp->render();
  }
}

@end
