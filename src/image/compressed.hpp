#ifndef COMPRESSED_H_UEQIDML9
#define COMPRESSED_H_UEQIDML9

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

class CompressedImage
{
  public:
    CompressedImage(
        size_t width,
        size_t height,
        size_t block_width,
        size_t block_height,
        size_t bytes_per_block_) :
      xdim(block_width), ydim(block_height),
      xsize(width), ysize(height),
      xblocks(width / xdim), yblocks(height / ydim),
      block_count(yblocks * xblocks),
      bytes_per_block(bytes_per_block_),
      buffer_size(block_count * bytes_per_block),
      buffer(new uint8_t[buffer_size])
    {
      assert(width  % xdim == 0);
      assert(height % ydim == 0);
    }

    CompressedImage(CompressedImage&& other) :
      xdim(other.xdim),
      ydim(other.ydim),
      xsize(other.xsize),
      ysize(other.ysize),
      xblocks(other.xblocks),
      yblocks(other.yblocks),
      block_count(other.block_count),
      bytes_per_block(other.bytes_per_block),
      buffer_size(other.buffer_size),
      buffer(other.buffer)
    {
      other.buffer = nullptr;
    }

    CompressedImage(const CompressedImage&) = delete;
    CompressedImage& operator=(const CompressedImage&) = delete;

    ~CompressedImage()
    {
      delete[] buffer;
    }

    size_t xdim, ydim;
    size_t xsize, ysize;
    size_t xblocks, yblocks;

    size_t block_count;

    size_t bytes_per_block;
    size_t buffer_size;
    uint8_t* buffer;
};

CompressedImage ReadCompressedFile(
    uint32_t magic,
    const char* file_path);

void WriteCompressedFile(
    uint32_t magic,
    const CompressedImage& compressed,
    const char* file_path);

#endif /* end of include guard: COMPRESSED_H_UEQIDML9 */
