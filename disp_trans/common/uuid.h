#pragma once

#include <sstream>
#include <random>
#include "../defines.h"
BEGIN_NS_AD
        class UUID
        {
        public:
            static std::string generate_uuid();
        };
END_NS_AD