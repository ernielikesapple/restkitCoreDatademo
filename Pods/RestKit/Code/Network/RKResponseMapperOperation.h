//
//  RKResponseMapperOperation.h
//  RestKit
//
//  Created by Blake Watters on 8/16/12.
//  Copyright (c) 2012 RestKit. All rights reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#import "RKMappingOperationDataSource.h"
#import "RKMapperOperation.h"
#import "RKMappingResult.h"

#if __has_include("CoreData.h")
@protocol RKManagedObjectCaching;
#endif

/**
 `RKResponseMapperOperation` is an `NSOperation` that provides support for performing object mapping on an `NSHTTPURLResponse` and its associated response data.
 
 This is an abstract base class encapsulating the common interface API for its concrete subclasses `RKObjectResponseMapperOperation` and `RKManagedObjectResponseMapperOperation`.
 
 The common behaviors encapsulated within `RKResponseMapperOperation` include:
 
 1. **Handling Empty Responses**: Empty response data (see note below) requires special handling depending on the status code of the HTTP response. If an empty response is loaded with a status code in 4xx (Client Error) range, an `NSError` in the `RKErrorDomain` is created with the `NSURLErrorBadServerResponse` code to indicate that the response was not processable. If an empty response is loaded with a status code in 2xx (Successful) range, the interpretation of the response is dependent on the value of `treatsEmptyResponseAsSuccess`. When `YES`, empty responses result in the successful completion of the operation with an `RKMappingResult` containing the targetObject of the operation, if any.
 1. **Deserializing Response Data**: When started, the operation attempts to deserialize the response data into a Foundation object representation using the `RKMIMETypeSerialization` class. This deserialized representation is then made available to subclass implementations that perform the actual object mapping work.
 
 ## How 'Empty' Responses are Evaluated
 
 Any `nil` response or `NSData` object with a length equal to zero is considered empty. To support a common behavior of the widely deployed Ruby on Rails Framework, `RKResponseMapperOperation` also considers a response containing a single space character to be empty. This type of response is generated by Rails whe `render :nothing => true` is invoked.
 
 ## Metadata Mapping

 The `RKResponseMapperOperation` class integrates with the metadata mapping architecture. Clients of the response mapper can provide a dictionary of metadata via the `mappingMetadata` property and it will be made available to the underlying `RKMapperOperation` executed to process the response body. In addition to any user supplied metadata, the response mapper makes the following metadata key paths available for mapping:

 1. `@metadata.HTTP.request.URL` - The `NSURL` object identifying the URL of the request that loaded the response.
 1. `@metadata.HTTP.request.method` - An `NSString` specifying the HTTP method of the request that loaded the response.
 1. `@metadata.HTTP.request.headers` - An `NSDictionary` object containing all HTTP headers and values for the request that loaded the response.
 1. `@metadata.HTTP.response.URL` - The `NSURL` object identifying the URL of the response.
 1. `@metadata.HTTP.response.headers` - An `NSDictionary` object containing all HTTP headers and values for the response.

 Please refer to the documentation accompanying `RKMappingOperation` for more details on metadata mapping.

 @see `RKMapperOperation`
 */
@interface RKResponseMapperOperation : NSOperation

///------------------------------------------------
/// @name Initializing a Response Mapping Operation
///------------------------------------------------

/**
 Initializes and returns a newly created response mapper operation with the given request, HTTP response, response data, and an array of `RKResponseDescriptor` objects.
 
 @param request The request object for which the response was loaded.
 @param response The HTTP response object to be used for object mapping.
 @param data The data loaded for the response body.
 @param responseDescriptors An array whose elements are `RKResponseDescriptor` objects specifying object mapping configurations that may be applied to the response.
 @return The receiver, initialized with the response, data, and response descriptor objects.
 */
- (instancetype)initWithRequest:(NSURLRequest *)request
             response:(NSHTTPURLResponse *)response
                 data:(NSData *)data
  responseDescriptors:(NSArray *)responseDescriptors NS_DESIGNATED_INITIALIZER;

///-----------------------------------------------
/// @name Accessing HTTP Request and Response Data
///-----------------------------------------------

/**
 An request object for which the response was loaded.
 */
@property (nonatomic, strong, readonly) NSURLRequest *request;

/**
 The response object that loaded the data that is to be object mapped by the operation. Cannot be `nil`.
 */
@property (nonatomic, strong, readonly) NSHTTPURLResponse *response;

/**
 The response data that is to be deserialized and mapped by the operation. May be `nil`.
 */
@property (nonatomic, strong, readonly) NSData *data;

///---------------------------------
/// @name Configuring Object Mapping
///---------------------------------

/**
 An array of `RKResponseDescriptor` objects that specify object mapping configurations that may be applied to the deserialized response data if they are found to match the response.
 
 @see `RKResponseDescriptor`
 */
@property (nonatomic, strong, readonly) NSArray *responseDescriptors;

/**
 The target object for the object mapping operation performed on the deserialized response data. May be `nil`.
 
 When object mapping is being performed against a known object, the targetObject is set to ensure that the mapping is applied to the appropriate object reference. When `nil`, the mapping operation will result in the fetching or creation of new objects as necessary to satisfy the mapping configuration.
 */
@property (nonatomic, strong) id targetObject;

/**
 The delegate for the `RKMapperOperation` created by the receiver to perform object mapping on the deserialized response data. May be `nil`.
 
 The delegate provides access to the details of the mapping process as it is executing. Be aware that the delegate will be invoked from the thread on which the mapping is executing.
 */
@property (nonatomic, weak) id<RKMapperOperationDelegate> mapperDelegate;

/**
 An optional dictionary of metadata to make available to mapping operations executed by the receiver.
 */
@property (nonatomic, copy) NSDictionary *mappingMetadata;

/**
 A Boolean value that indicates if the receiver should consider empty responses as being successfully mapped even though no mapping is actually performed.

 When `YES` and the response data is empty (see below), a mapping result will be returned containing the target object (if any). Otherwise, the response data will be pass through to the parser which may generate an error.

 **Default:** `YES`

 @warning To support the Ruby on Rails behavior of rendering a single space character on invocation of `render :nothing => true`, a response body's containing only a single space is treated as empty.
 */
@property (nonatomic, assign) BOOL treatsEmptyResponseAsSuccess;

/**
 Returns a dictionary of key path to `RKMapping` objects that are applicable to mapping the response. This is determined by evaluating the URL and status codes of the response against the set of `responseDescriptors`.

 @see `RKResponseDescriptor`
 */
@property (nonatomic, strong, readonly) NSDictionary *responseMappingsDictionary;

/**
 Returns an array containing all `RKResponseDescriptor` objects in the configured `responseDescriptors` array that were found to match the response.
 
 @see `responseDescriptors`
 @see `RKResponseDescriptor`
 */
@property (nonatomic, strong, readonly) NSArray *matchingResponseDescriptors;

///--------------------------------
/// @name Accessing Mapping Results
///--------------------------------

/**
 The results of performing object mapping on the deserialized response data. In the event that the operation has failed, the value will is `nil`.
 
 The `keyPath` of each `RKResponseDescriptor` from the `responseDescriptors` set that was successfully mapped from the response data will appear as an entry in the mapping result.
 */
@property (nonatomic, strong, readonly) RKMappingResult *mappingResult;

/**
 The error, if any, that occured during execution of the operation.
 */
@property (nonatomic, strong, readonly) NSError *error;

///----------------------------
/// @name Configuring Callbacks
///----------------------------

/**
 Sets a block to be executed before the response mapper operation begins mapping the deserialized response body, providing an opportunity to manipulate the mappable representation input before mapping begins.
 
 @param block A block object to be executed before the deserialized response is passed to the response mapper. The block has an `id` return type and must return a dictionary or array of dictionaries corresponding to the object representations that are to be mapped. The block accepts a single argument: the deserialized response data that was loaded via HTTP. If you do not wish to make any chances to the response body before mapping begins, the block should return the value passed in the `deserializedResponseBody` block argument. Returning `nil` will decline the mapping from proceeding and fail the operation with an error with the `RKMappingErrorMappingDeclined` code.
 @warning The deserialized response body may or may not be immutable depending on the implementation details of the `RKSerialization` class that deserialized the response. If you wish to make changes to the mappable object representations, you must obtain a mutable copy of the response body input.
 */
- (void)setWillMapDeserializedResponseBlock:(id (^)(id deserializedResponseBody))block;

/**
 Sets a block to be executed when the response mapper operation has completed its mapping activities. This method is distinct from the `completionBlock` because it is invoked while the operation is still executing. This block is guaranteed to be called even if the receiver is cancelled before it has been started.
 
 @param block A block object to be executed when the response mapping is finished. The block has no return value and accepts two arguments: an `RKNappingResult` object that was mapped from the response or an `NSError` error indicating that the mapping has failed.
 */
- (void)setDidFinishMappingBlock:(void(^)(RKMappingResult *mappingResult, NSError *error))block;

///--------------------------------------------------------
/// @name Registering a Mapping Operation Data Source Class
///--------------------------------------------------------

/**
 Registers the given data source class to to be used for mapper operations constructed by instances of the receiver.
 
 **NOTE**: The receiver class is significant to the registration: `[RKObjectResponseMapperOperation registerMappingOperationDataSourceClass:[MyDataSourceClass class]]` registers a data source for use with instances of `RKObjectResponseMapperOperation` exclusively. When registering a data source for `RKManagedObjectResponseMapperOperation` the given class must inherit from `RKManagedObjectMappingOperationDataSource`.
 
 @param dataSourceClass The class conforming to the RKMappingOperationDataSource protocol to be registered for use with mapper operations.
 */
+ (void)registerMappingOperationDataSourceClass:(Class<RKMappingOperationDataSource>)dataSourceClass;

@end

/**
 `RKObjectResponseMapperOperation` is an `RKResponseMapperOperation` subclass that provides support for performing object mapping for mappings that target `NSObject` derived classes. It does not require a data source to perform its work.
 */
@interface RKObjectResponseMapperOperation : RKResponseMapperOperation
@end

#if __has_include("CoreData.h")
/**
 `RKManagedObjectResponseMapperOperation` is an `RKResponseMapperOperation` subclass that provides support for performing object mapping using `RKEntityMapping` objects that target `NSManagedObject` derived classes. It requires an `NSManagedObjectContext` and a configured `RKManagedObjectMappingOperationDataSource` data source to execute successfully.
 
 Performing response mapping that targets Core Data managed objects imposes some additional constraints on the process that the developer should understand thoroughly:
 
 1. **Permanent Managed Object IDs**: When using managed object contexts in a parent-child configuration, it is important to obtain a permanent `NSManagedObjectID` for any existing objects that are to be mapped. Mapping that occur against objecs with temporary managedObjectID's cannot be retrieved across contexts by ID. If executing an `RKManagedObjectResponseMapperOperation` against a `NSManagedObject` targetObject with a temporary ID.
 1. **Persisting Mapped Objects**: Instances of `RKManagedObjectResponseMapperOperation` do **NOT** perform any persistence on the `NSManagedObject` in which the mapping occurs. This is by design and ensures that the operation can be used to compose higher level components that handle persistence. It is the developer's responsibility to ensure that the mapped managed objects are eventually persisted.
 
 @see `RKManagedObjectMappingOperationDataSource`
 @see `[NSManagedObjectContext obtainPermanentIDsForObjects:error:]`
 */
@interface RKManagedObjectResponseMapperOperation : RKResponseMapperOperation

///----------------------------
/// @name Configuring Core Data
///----------------------------

/**
 The managed object context in which the mapping will be performed. 
 
 @warning The `NSManagedObjectContext` given **must** have a `concurrencyType` of either `NSPrivateQueueConcurrencyType` or `NSMainQueueConcurrencyType`. Thread confined contexts are not supported.
 */
@property (nonatomic, strong) NSManagedObjectContext *managedObjectContext;

/**
 An object implementing the `RKManagedObjectCaching` protocol to be used for retrieving existing `NSManagedObject` instances by identification attributes. If `nil`, existing object cannot be retrieved and new objects will be created for all mappable content within the response data, likely resulting in the creation of duplicate objects.
 
 @see `RKManagedObjectCaching`
 */
@property (nonatomic, weak) id<RKManagedObjectCaching> managedObjectCache;

/**
 The permanent `NSManagedObjectID` for the target object of the mapping operation. During mapping, an instance local to the `managedObjectContext` is fetched and used to perform the mapping operation.

 If `nil` and the `targetObject` is a managed object, the `objectID` of the target object will be used.
 */
@property (nonatomic, copy) NSManagedObjectID *targetObjectID;

@end

#endif

///----------------
/// @name Functions
///----------------

/**
 Returns a representation of a mapping result as an `NSError` value.
 
 The returned `NSError` object is in the `RKErrorDomain` domain and has the `RKMappingErrorFromMappingResult` code. The value for the `NSLocalizedDescriptionKey` is computed by retrieving the objects in the mapping result as an array, evaluating `valueForKeyPath:@"description"` against the array, and joining the returned error messages by comma to form a single string value. The source error objects are returned with the `NSError` in the `userInfo` dictionary under the `RKObjectMapperErrorObjectsKey` key.
 
 This implementation assumes that the class used to represent the response error will return a string description of the client side error when sent the `description` message.
 
 @return An error object representing the objects contained in the mapping result.
 @see `RKErrorMessage`
 */
NSError *RKErrorFromMappingResult(RKMappingResult *mappingResult);