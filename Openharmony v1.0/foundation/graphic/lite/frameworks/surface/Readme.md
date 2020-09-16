
### Surface Sequence Diagram
```plantuml

actor Producer
participant "Surface" as SurfaceClient <<Client>>
control BufferClientProducer
collections BufferQueue
control BufferManager
control BufferQueueProducer

Producer -> SurfaceClient ++: RequestBuffer
SurfaceClient -> BufferClientProducer ++: RequestBuffer
BufferClientProducer -> BufferQueueProducer++ : <<Request Buffer With IPC Communication>>
BufferQueueProducer -> BufferQueue ++: Dequeue
opt free list is empty
BufferQueue -> BufferManager ++: AllocBuffer
create entity Buffer
BufferManager -> Buffer : new Buffer
note right : allocate buffer with virtural or phiscal memory.
return buffer
BufferQueue -> BufferQueue : push to free list
end
BufferQueue -> BufferQueue : pop from free list
return buffer
return buffer
BufferClientProducer -> BufferManager++ : MapBuffer
return success
return buffer
return buffer

Producer -> Producer : write data to buffer

Producer -> SurfaceClient ++: FlushBuffer
SurfaceClient -> BufferClientProducer ++: FlushBuffer
BufferClientProducer -> BufferQueueProducer++ : <<Flush Buffer With IPC Communication>>
BufferQueueProducer -> BufferQueue ++: Enqueue
BufferQueue -> BufferQueue : push to dirty list
return success
return success
BufferClientProducer -> BufferManager++ : UnmapBuffer
return success
return success
return success

control BufferQueueConsumer
participant "Surface" as SurfaceServer <<Server>>
actor Consumer
Consumer -> SurfaceServer ++: AcquireBuffer
SurfaceServer -> BufferQueueConsumer ++: AcquireBuffer
BufferQueueConsumer -> BufferQueue ++: Acquire
BufferQueue -> BufferQueue : pop from dirty list
return buffer
return buffer
return buffer

Consumer -> Consumer : read data from buffer

Consumer -> SurfaceServer ++: ReleaseBuffer
SurfaceServer -> BufferQueueConsumer ++: ReleaseBuffer
BufferQueueConsumer -> BufferQueue ++: Release
BufferQueue -> BufferQueue: push to free list
return success
return success
return success
```

###Surface State Diagram

```plantuml
[*] --> NONE : Allocate Buffer
NONE --> DEQUEUE : Dequeue Buffer
DEQUEUE --> ENQUEUE : Enqueue Buffer
DEQUEUE --> FREE : Cancel Buffer
ENQUEUE --> ACQUIRE : Acquire Buffer
ACQUIRE --> FREE : Release Buffer
FREE -->DEQUEUE : Dequeue Buffer

FREE --> [*] : Free Buffer
```

###Surface Class Diagram
```plantuml
namespace OHOS  {
    class Surface {
        __Methods__
        +{static}GenericSurfaceByIpcIo(IpcIo& io):Surface*
        +Surface()
        +RequestBuffer(uint8_t):SurfaceBuffer*
        +FlushBuffer(SurfaceBuffer*):bool
        +AcquireBuffer():SurfaceBuffer*
        +CancelBuffer(SurfaceBuffer*)
        +ReleaseBuffer(const SurfaceBuffer& buffer):bool
        +RegisterConsumerListener(IBufferConsumerListener& listener)
        +UnregisterConsumerListener()
        +WriteIoIpcIo(IpcIo& io)
        __Attributes__
        -BufferProducer producer_
        -BufferQueueConsumer consumer_
    }
    abstract class BufferProducer {
        __Methods__
        +{abstract} RequestBuffer(uint8_t):SurfaceBuffer*
        +{abstract} FlushBuffer(SurfaceBuffer*):bool
        +{abstract} CancelBuffer(SurfaceBuffer*)
    }
    class BufferClientProducer {
        __Methods__
        +RequestBuffer(uint8_t):SurfaceBuffer*
        +FlushBuffer(SurfaceBuffer*):bool
        +CancelBuffer(SurfaceBuffer*)
    }
    class BufferQueueProducer {
        __Methods__
        +RequestBuffer(uint8_t):SurfaceBuffer*
        +FlushBuffer(SurfaceBuffer*):bool
        +CancelBuffer(SurfaceBuffer*)
        __Attributes__
        -BufferQueue queue_
    }
    class BufferQueueConsumer {
        __Methods__
        +AcquireBuffer():SurfaceBuffer*
        +ReleaseBuffer(const SurfaceBuffer&):bool
        __Attributes__
        -BufferQueue queue_
    }
    class BufferQueue {
        __Methods__
        +Dequeue(uint8_t):SurfaceBuffer*
        +Enqueue(SurfaceBuffer& buffer):int32_t
        +Acquire():SurfaceBuffer*
        +Release(const SurfaceBuffer&):bool
        +Cancel(const SurfaceBuffer&):int32_t
        __Attributes__
        -List<SurfaceBuffer*> allBuffers
        -List<SurfaceBuffer*> freeLists
        -List<SurfaceBuffer*> dirtyLists
    }
    abstract class BufferManager {
        +{abstract} AllocBuffer(uint32_t, uint32_t) : SurfaceBuffer*
        +{abstract} FreeBuffer(SurfaceBuffer*)
        +{abstract} FlushCache(const SurfaceBuffer& buffer) : int32_t
        +{abstract} MapBuffer(SurfaceBuffer&)
        +{abstract} UnmapBuffer(SurfaceBuffer&)
    }
    class BufferManagerDumb {
        +AllocBuffer(uint32_t, uint32_t) : SurfaceBuffer*
        +FreeBuffer(SurfaceBuffer*)
        +FlushCache(const SurfaceBuffer& buffer) : int32_t
        +MapBuffer(SurfaceBuffer&)
        +UnmapBuffer(SurfaceBuffer&)
    }
    class BufferManagerShm {
        +AllocBuffer(uint32_t, uint32_t) : SurfaceBuffer*
        +FreeBuffer(SurfaceBuffer*)
        +FlushCache(const SurfaceBuffer& buffer) : int32_t
        +MapBuffer(SurfaceBuffer&)
        +UnmapBuffer(SurfaceBuffer&)
    }
    class SurfaceBuffer {
        __Methods__
        +GetVirAddr() : void*
        +SetInt32(uint32_t, int32_t) : int32_t
        +GetInt32(uint32_t, int32_t&) : int32_t
        +SetInt64(uint32_t, int64_t) : int32_t
        +GetInt64(uint32_t, int64_t&) : int32_t
        +ReadFromIpcIo(IpcIo&)
        +WriteToIpcIo(IpcIo&)
        +CopyExtraData(SurfaceBuffer&)
        +ClearExtraData()
    }

    BufferProducer <|-- BufferClientProducer
    BufferProducer <|-- BufferQueueProducer
    BufferManager <|-- BufferManagerDumb
    BufferManager <|-- BufferManagerShm
    BufferQueue *- SurfaceBuffer : have more >
    BufferManagerDumb ..> SurfaceBuffer
    BufferManagerShm ..> SurfaceBuffer
    Surface o-- BufferProducer
    Surface o-- BufferQueueConsumer
    BufferQueueConsumer *-- BufferQueue
    BufferQueueProducer *-- BufferQueue
    BufferManager .. BufferQueue
}
```
