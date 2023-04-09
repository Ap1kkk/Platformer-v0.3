#include "Chunk.h"

ChunkId Chunk::staticIdCounter = 0;

Chunk::Chunk(SharedContext sharedContext, ObjectContext objectContext) : sharedContext(sharedContext), objectContext(objectContext), chunkId(staticIdCounter++)
{

}
}
