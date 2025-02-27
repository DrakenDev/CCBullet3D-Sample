/*
 * CC3Fog.h
 *
 * cocos3d 0.6.1
 * Author: Bill Hollings
 * Copyright (c) 2010-2011 The Brenwill Workshop Ltd. All rights reserved.
 * http://www.brenwill.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * http://en.wikipedia.org/wiki/MIT_License
 */

/** @file */	// Doxygen marker

#import "CC3Foundation.h"
#import "CCAction.h"
#import "CCProtocols.h"


/**
 * CC3Fog controls fog in the 3D world.
 *
 * Fog color is controlled by the floatColor property, or via support for the CCRGBAProtocol
 * protocol. However, be aware that alpha channels and opacity info are ignored by the OpenGL
 * implementation of fog effects. See the notes of the color property for more info.
 *
 * The style of attenuation imposed by the fog is set by the attenuationMode property.
 * See the notes of that property for information about how fog attenuates visibility.
 *
 * Using the performanceHint property, you can direct the GL engine to trade off between
 * faster or nicer rendering quality.
 */
@interface CC3Fog : NSObject <CCRGBAProtocol, NSCopying> {
	ccColor4F floatColor;
	GLenum attenuationMode;
	GLenum performanceHint;
	GLfloat density;
	GLfloat startDistance;
	GLfloat endDistance;
	BOOL visible;
	BOOL isRunning;
}

/**
 * Controls whether the fog should be drawn into the world.
 *
 * The initial value of this property is YES.
 */
@property(nonatomic, assign) BOOL visible;

/**
 * The color of the fog.
 * 
 * CC3Fog also supports the CCRGBAProtocol protocol, allowing the color of the fog
 * to be manipulated by the CCTint interval action.
 *
 * Although this color value, and the CCRGBAProtocol protocol support setting opacity,
 * fog in OpenGL ES does not make use of opacity information, so any changes to the
 * alpha channel of this property, or to the opacity property will be ignored.
 *
 * The initial value of this property is kCCC4FBlack.
 */
@property(nonatomic, assign) ccColor4F floatColor;

/**
 * Indicates how the fog attenuates visibility with distance.
 *
 * The value of this property must be one of the following sybolic constants:
 * GL_LINEAR, GL_EXP or GL_EXP2.
 *
 * When the value of this property is GL_LINEAR, the relative visibility of an object
 * in the fog will be determined by the linear function ((e - z) / (e - s)), where
 * s is the value of the start property, e is the value of the end property, and z is
 * the distance of the object from the camera
 *
 * When the value of this property is GL_EXP, the relative visibility of an object in
 * the fog will be determined by the exponential function e^(-(d - z)), where d is the
 * value of the density property and z is the distance of the object from the camera.
 *
 * When the value of this property is GL_EXP2, the relative visibility of an object in
 * the fog will be determined by the exponential function e^(-(d - z)^2), where d is the
 * value of the density property and z is the distance of the object from the camera.
 *
 * The initial value of this property is GL_EXP2.
 */
@property(nonatomic, assign) GLenum attenuationMode;

/**
 * Indicates how the GL engine should trade off between rendering quality and speed.
 * The value of this property should be one of GL_FASTEST, GL_NICEST, or GL_DONT_CARE.
 *
 * The initial value of this property is GL_DONT_CARE.
 */
@property(nonatomic, assign) GLenum performanceHint;

/**
 * The density value used in the exponential functions. This property is only used
 * when the attenuationMode property is set to GL_EXP or GL_EXP2.
 *
 * See the description of the attenuationMode for a discussion of how the exponential
 * functions determine visibility.
 *
 * The initial value of this property is 1.0.
 */
@property(nonatomic, assign) GLfloat density;

/**
 * The distance from the camera, at which linear attenuation starts. Objects between
 * this distance and the near clipping plane of the camera will be completly visible.
 *
 * This property is only used when the attenuationMode property is set to GL_LINEAR.
 *
 * See the description of the attenuationMode for a discussion of how the linear
 * function determine visibility.
 *
 * The initial value of this property is 0.0.
 */
@property(nonatomic, assign) GLfloat startDistance;

/**
 * The distance from the camera, at which linear attenuation ends. Objects between
 * this distance and the far clipping plane of the camera will be completely obscured.
 *
 * This property is only used when the attenuationMode property is set to GL_LINEAR.
 *
 * See the description of the attenuationMode for a discussion of how the linear
 * function determine visibility.
 *
 * The initial value of this property is 1.0.
 */
@property(nonatomic, assign) GLfloat endDistance;

/**
 * Indicates whether the dynamic behaviour of this fog is enabled.
 *
 * Setting this property affects both internal activities driven by the update process,
 * and any CCActions controling this node. Setting this property to NO will effectively
 * pause all update and CCAction behaviour on the node. Setting this property to YES will
 * effectively resume the update and CCAction behaviour.
 */
@property(nonatomic, assign) BOOL isRunning;


#pragma mark Allocation and initialization

/** Allocates and initializes an autoreleased instance. */
+(id) fog;


#pragma mark Updating

/**
 * This method is invoked periodically when the fog is to be updated.
 *
 * Typcially this method is invoked automatically from the CC3World instance via a scheduled update,
 * but may also be invoked by some other periodic operation, or even directly by the application.
 *
 * This method is invoked asynchronously to the frame rendering animation loop, to keep the
 * processing of model updates separate from OpenGL ES drawing.
 *
 * The dt argument gives the interval, in seconds, since the previous update. This value can be
 * used to create realistic real-time motion that is independent of specific frame or update rates.
 *
 * If this instance is not running, as indicated by the isRunning property, this method does nothing.
 *
 * As implemented, this method does nothing. Subclasses may override.
 *
 * This method is invoked automatically at each scheduled update. Usually, the application
 * never needs to invoke this method directly.
 */
-(void) update: (ccTime)dt;


#pragma mark Drawing

/** If the visible property is set to YES, draws the fog to the GL engine. */
-(void) draw;

/** Disables the rendering of fog in the GL engine. */
-(void) unbind;

/** Disables the rendering of fog in the GL engine. */
+(void) unbind;


#pragma mark CC3Node actions

/**
 * Executes an action, and returns the action that is executed.
 * This fog becomes the action's target.
 */
-(CCAction*) runAction: (CCAction*) action;

/** Removes all actions from the running action list */
-(void) stopAllActions;

/** Removes an action from the running action list */
-(void) stopAction: (CCAction*) action;

/** Removes an action from the running action list given its tag */
-(void) stopActionByTag:(int) tag;

/** Gets an action from the running action list given its tag */
-(CCAction*) getActionByTag:(int) tag;

/**
 * Returns the numbers of actions that are running plus the ones that are scheduled to run
 * (actions in actionsToAdd and actions arrays).
 * Composable actions are counted as 1 action. Example:
 *    If you are running 1 Sequence of 7 actions, it will return 1.
 *    If you are running 7 Sequences of 2 actions, it will return 7.
 */
-(int) numberOfRunningActions;

@end
