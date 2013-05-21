/*
 Copyright (C) 2010-2013 Kristian Duske
 
 This file is part of TrenchBroom.
 
 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with TrenchBroom.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __TrenchBroom__Token__
#define __TrenchBroom__Token__

#include "StringUtils.h"

#include <cassert>
#include <cstring>

namespace TrenchBroom {
    namespace IO {
        template <typename Type>
        class TokenTemplate {
        private:
            Type m_type;
            const char* m_begin;
            const char* m_end;
            size_t m_position;
            size_t m_line;
            size_t m_column;
        public:
            TokenTemplate() :
            m_type(0),
            m_begin(NULL),
            m_end(NULL),
            m_position(0),
            m_line(0),
            m_column(0) {}
            
            TokenTemplate(const Type type, const char* begin, const char* end, const size_t position, const size_t line, const size_t column) :
            m_type(type),
            m_begin(begin),
            m_end(end),
            m_position(position),
            m_line(line),
            m_column(column) {
                assert(end >= begin);
            }
            
            inline Type type() const {
                return m_type;
            }
            
            inline const String data() const {
                return String(m_begin, length());
            }
            
            inline size_t position() const {
                return m_position;
            }
            
            inline size_t length() const {
                return static_cast<size_t>(m_end - m_begin);
            }
            
            inline size_t line() const {
                return m_line;
            }
            
            inline size_t column() const {
                return m_column;
            }
            
            inline double toFloat() const {
                static char buffer[64];
                assert(length() < 64);
                
                memcpy(buffer, m_begin, length());
                buffer[length()] = 0;
                const double f = std::atof(buffer);
                return f;
            }
            
            inline int toInteger() const {
                static char buffer[64];
                assert(length() < 64);
                
                memcpy(buffer, m_begin, length());
                buffer[length()] = 0;
                const int i = static_cast<int>(std::atoi(buffer));
                return i;
            }
        };
    }
}

#endif /* defined(__TrenchBroom__Token__) */
