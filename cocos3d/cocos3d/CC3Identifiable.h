/*
 * CC3Identifiable.h
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

/**
 * This is a base subclass for any class that uses tags or names to identify individual instances.
 * Instances can be initialized with either or both a tag and a name. Instances initialized without
 * an explcit tag will have a unique tag automatically generated and assigned.
 *
 * You can assign your own data to instances of CC3Identifiable or its subclasses through the
 * userData property.
 *
 * When overriding initialization, subclasses typically need only override the most generic
 * initializer, initWithTag:withName:.
 */
@interface CC3Identifiable : NSObject <NSCopying> {
	GLuint tag;
	NSString* name;
	void* userData;
}

/**
 * An arbitrary identification. Useful for keeping track of instances. Unique tags are not explicitly
 * required, but are highly recommended. In most cases, it is best to just let the tag be assigned
 * automatically by using an initializer that does not explicitly set the tag.
 */
@property(nonatomic, assign) GLuint tag;

/**
 * An arbitrary name for this node. It is not necessary to give all identifiable objects a name,
 * but can be useful for retrieving objects at runtime, and for identifying objects during development.
 * Names need not be unique, are not automatically assigned, and leaving the name as nil is acceptable.
 */
@property(nonatomic, retain) NSString* name;

/**
 * Application-specific data associated with this object.
 *
 * You can use this property to add any data you want to an instance of CC3Identifiable or
 * its concrete subclasses (CC3Node, CC3Mesh, CC3Material, CC3Texture, etc.). Since this is
 * a generic pointer, you can store any type of data, such as an object, structure, primitive,
 * or array.
 *
 * This data is not retained by this instance, and is not managed by the cocos3d framework.
 * It is the responsibility of the application to manage the allocation, retention, and
 * disposal of this data.
 *
 * To assist in managing this data, the methods initUserData and releaseUserData are invoked
 * automatically during the initialization and deallocation of each instance of this class.
 * In this abstract class, these methods do nothing, but, if appropriate, you can override
 * these methods by adding extention categories to the concrete subclasses of CC3Identifiable,
 * (CC3Node, CC3Mesh, CC3Material, CC3Texture, etc.), to create, retain and dispose of the data.
 *
 * In this abstract class, this property is not retained. You can override the accessor
 * methods by creating extension categories for the concrete subclasses, (CC3Node, CC3Mesh,
 * CC3Material, CC3Texture, etc.), in order to retain the data if appropriate.
 */
@property(nonatomic, assign) void* userData;


#pragma mark Allocation and initialization

/**
 * Initializes this unnamed instance with an automatically generated unique tag value.
 * The tag value will be generated automatically via the method nextTag.
 */
-(id) init;

/** Initializes this unnamed instance with the specified tag. */
-(id) initWithTag: (GLuint) aTag;

/**
 * Initializes this instance with the specified name and an automatically generated unique
 * tag value. The tag value will be generated automatically via the method nextTag.
 */
-(id) initWithName: (NSString*) aName;

/**
 * Initializes this instance with the specified tag and name.
 * When overriding initialization, subclasses typically need only override this initializer.
 */
-(id) initWithTag: (GLuint) aTag withName: (NSString*) aName;

/**
 * Invoked automatically from the init* family of methods to initialize the userData reference.
 *
 * In this abstract class, this method does nothing. You can override this method by creating
 * extension categories for the concrete subclasses, (CC3Node, CC3Mesh, CC3Material, CC3Texture,
 * etc.), if the userData can be initialized and retained in self-contained manner.
 */
-(void) initUserData;

/**
 * Invoked automatically from the dealloc method to release or dispose of the data referenced
 * in the userData property.
 *
 * In this abstract class, this method does nothing. You can override this method by creating
 * extension categories for the concrete subclasses (CC3Node, CC3Mesh, CC3Material, CC3Texture,
 * etc.), to release or dispose of the data referenced in the userData property.
 */
-(void) releaseUserData;

/**
 * Returns a newly allocated (retained) copy of this instance. The new copy will have
 * the same name as this instance, but will have a unique tag.
 *
 * The returned instance is retained. It is the responsiblity of the caller to manage
 * the lifecycle of the returned instance and perform the corresponding invocation of
 * the release method at the appropriate time.
 *
 * This copy operation is a deep copy. Copies of most of the content of the original
 * will be created as well. For structural subclasses, such as CC3Node, copies will
 * be made of each structual element (eg- child nodes). Some exceptions are made.
 * For instance, copies are generally not made for fixed, voluminous content such as
 * mesh data. In addition, subclasses may excuse themselves from being copied through
 * the shouldIncludeInDeepCopy property.
 *
 * This copy operation is a deep copy. Copies of most of the content of the original
 * will be created as well. For structural subclasses, such as CC3Node, copies will
 * be made of each structual element (eg- child nodes). Some exceptions are made.
 * For instance, copies are generally not made for fixed, voluminous content such as
 * mesh data. In addition, subclasses may excuse themselves from being copied through
 * the shouldIncludeInDeepCopy property.
 *
 * The copy... methods may often be used to duplicate an instance many times, to create
 * large number of similar instances to populate a game. To help you verify that you are
 * correctly releasing and deallocating all these copies, you can use the instanceCount
 * class method to get a current count of the total number of instances of all subclasses
 * of CC3Identifiable,
 *
 * Subclasses that extend copying should not override this method, but should override
 * the populateFrom: method instead.
 */
 -(id) copy;

/**
 * Returns a newly allocated (retained) copy of this instance. The new copy
 * will have its name set to the specified name, and will have a unique tag.
 *
 * The returned instance is retained. It is the responsiblity of the caller to manage
 * the lifecycle of the returned instance and perform the corresponding invocation of
 * the release method at the appropriate time.
 *
 * This copy operation is a deep copy. Copies of most of the content of the original
 * will be created as well. For structural subclasses, such as CC3Node, copies will
 * be made of each structual element (eg- child nodes). Some exceptions are made.
 * For instance, copies are generally not made for fixed, voluminous content such as
 * mesh data. In addition, subclasses may excuse themselves from being copied through
 * the shouldIncludeInDeepCopy property.
 *
 * The copy... methods may often be used to duplicate an instance many times, to create
 * large number of similar instances to populate a game. To help you verify that you are
 * correctly releasing and deallocating all these copies, you can use the instanceCount
 * class method to get a current count of the total number of instances of all subclasses
 * of CC3Identifiable,
 *
 * Subclasses that extend copying should not override this method, but should override
 * the populateFrom: method instead.
 */
-(id) copyWithName: (NSString*) aName;

/**
 * Returns a newly allocated (retained) copy of this instance. The new copy
 * will have its name set to the specified name, and will have a unique tag.
 *
 * The returned instance is retained. It is the responsiblity of the caller to manage
 * the lifecycle of the returned instance and perform the corresponding invocation of
 * the release method at the appropriate time.
 *
 * This copy operation is a deep copy. Copies of most of the content of the original
 * will be created as well. For structural subclasses, such as CC3Node, copies will
 * be made of each structual element (eg- child nodes). Some exceptions are made.
 * For instance, copies are generally not made for fixed, voluminous content such as
 * mesh data. In addition, subclasses may excuse themselves from being copied through
 * the shouldIncludeInDeepCopy property.
 *
 * The copy... methods may often be used to duplicate an instance many times, to create
 * large number of similar instances to populate a game. To help you verify that you are
 * correctly releasing and deallocating all these copies, you can use the instanceCount
 * class method to get a current count of the total number of instances of all subclasses
 * of CC3Identifiable,
 *
 * Subclasses that extend copying should not override this method, but should override
 * the populateFrom: method instead.
 */
-(id) copyWithZone: (NSZone*) zone withName: (NSString*) aName;

/**
 * Returns a newly allocated (retained) copy of this instance. The new copy
 * will be an instance of the specified class, will have its name set to the
 * specified name, and will have a unique tag.
 *
 * Care should be taken when choosing the class to be instantiated. If the class is
 * different than that of this instance, the populateFrom: method of that class must
 * be compatible with the contents of this instance.
 *
 * The returned instance is retained. It is the responsiblity of the caller to manage
 * the lifecycle of the returned instance and perform the corresponding invocation of
 * the release method at the appropriate time.
 *
 * This copy operation is a deep copy. Copies of most of the content of the original
 * will be created as well. For structural subclasses, such as CC3Node, copies will
 * be made of each structual element (eg- child nodes). Some exceptions are made.
 * For instance, copies are generally not made for fixed, voluminous content such as
 * mesh data. In addition, subclasses may excuse themselves from being copied through
 * the shouldIncludeInDeepCopy property.
 *
 * The copy... methods may often be used to duplicate an instance many times, to create
 * large number of similar instances to populate a game. To help you verify that you are
 * correctly releasing and deallocating all these copies, you can use the instanceCount
 * class method to get a current count of the total number of instances of all subclasses
 * of CC3Identifiable,
 *
 * Subclasses that extend copying should not override this method, but should override
 * the populateFrom: method instead.
 */
-(id) copyWithName: (NSString*) aName asClass: (Class) aClass;

/**
 * Returns a newly allocated (retained) copy of this instance. The new copy
 * will be an instance of the specified class, will have its name set to the
 * specified name, and will have a unique tag.
 *
 * Care should be taken when choosing the class to be instantiated. If the class is
 * different than that of this instance, the populateFrom: method of that class must
 * be compatible with the contents of this instance.
 *
 * The returned instance is retained. It is the responsiblity of the caller to manage
 * the lifecycle of the returned instance and perform the corresponding invocation of
 * the release method at the appropriate time.
 *
 * This copy operation is a deep copy. Copies of most of the content of the original
 * will be created as well. For structural subclasses, such as CC3Node, copies will
 * be made of each structual element (eg- child nodes). Some exceptions are made.
 * For instance, copies are generally not made for fixed, voluminous content such as
 * mesh data. In addition, subclasses may excuse themselves from being copied through
 * the shouldIncludeInDeepCopy property.
 *
 * The copy... methods may often be used to duplicate an instance many times, to create
 * large number of similar instances to populate a game. To help you verify that you are
 * correctly releasing and deallocating all these copies, you can use the instanceCount
 * class method to get a current count of the total number of instances of all subclasses
 * of CC3Identifiable,
 *
 * Subclasses that extend copying should not override this method, but should override
 * the populateFrom: method instead.
 */
-(id) copyWithZone: (NSZone*) zone withName: (NSString*) aName asClass: (Class) aClass;

/**
 * Returns whether this instance should be included in a deep copy.
 *
 * This method simply returns YES by default, and in most cases this is sufficient.
 * However, for some structural subclasses (notably subclasses of CC3Node) it may
 * be desirable to not copy some components.
 *
 * This property is not universally automatically applied or honoured. It is
 * up to the invoker and invokee to agree on when to make use of this property.
 */
@property(nonatomic, readonly) BOOL shouldIncludeInDeepCopy;
	
/**
 * Returns a unique tag value to identify instances. This value is unique across all instances
 * of all subclasses. The initial value returned will be one, and subsequent calls will increment
 * the value retuned on each call. The starting value can be reset back to one via the
 * resetTagAllocation method.
 */
-(GLuint) nextTag;

/** Resets the allocation of new tags to resume at one again. */
+(void) resetTagAllocation;

/**
 * Indicates the total number of active instances, over all subclasses, that have been allocated
 * and initialized, but not deallocated. This can be useful when creating hordes of 3D objects,
 * to verify that your application is properly deallocating them again when you are done with them.
 */
+(GLint) instanceCount;

/**
 * Returns a string containing a more complete description of this object.
 *
 * This implementation simply invokes the description method. Subclasses with more
 * substantial content can override to provide much more information.
 */
-(NSString*) fullDescription;

@end
