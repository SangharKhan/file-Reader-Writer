set(SRCS_FILE
      ReadWrite.cpp
   )
   
set(HEADERS_FILE
      ../include/ReadWrite.h
    )

add_library(ClassReadWrite STATIC ${SRCS_FILE} ${HEADERS_FILE} stdc++fs)

