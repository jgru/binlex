#include <iostream>
#include <memory>
#include <set>
#include <LIEF/PE.hpp>
#include "common.h"

#ifndef PE_H
#define PE_H

#define PE_MAX_SECTIONS 256

using namespace std;
using namespace LIEF::PE;

namespace binlex {
    class PE {
        private:
            void ParseSections();
        public:
            MACHINE_TYPES mode = MACHINE_TYPES::IMAGE_FILE_MACHINE_UNKNOWN;
            unique_ptr<LIEF::PE::Binary> binary;
            struct Section {
                uint offset;
                int size;
                void *data;
                set<uint64_t> functions;
            };
            PE();
            struct Section sections[PE_MAX_SECTIONS];
            /**
            @param file_path path to the executable
            @return bool
            */
            bool ReadFile(char *file_path);
            /**
            @param data pointer to executable in memory
            @param size size of the data
            @return bool
            */
            bool ReadBuffer(void *data, size_t size);
            /**
            Setup to Read Specific PE Format
            @param input_mode MACHINE_TYPES::IMAGE_FILE_MACHINE_<arch>
            @return bool
            */
            bool Setup(MACHINE_TYPES input_mode);
            ~PE();
    };
};

#endif