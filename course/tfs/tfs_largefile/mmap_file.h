#ifndef DONGNAO_LARGEFILE_MMAPFILE_H_
#define DONGNAO_LARGEFILE_MMAPFILE_H_

#include "common.h"
#include <unistd.h>


namespace dongnao
{
  namespace largefile
  {
    class MMapFile
    {
      public:
        MMapFile();
        explicit MMapFile(const int fd);
        MMapFile(const MMapOption& mmap_option, const int fd);
        ~MMapFile();

        bool sync_file();
        bool map_file(const bool write = false);
        bool remap_file();
        void* get_data() const;
        int32_t get_size() const;
        bool munmap_file();

      private:
        bool ensure_file_size(const int32_t size);

      private:
        int32_t size_;
        int fd_;
        void* data_;
        MMapOption mmap_file_option_;
    };
  }
}
#endif //DONGNAO_LARGEFILE_MMAPFILE_H_
