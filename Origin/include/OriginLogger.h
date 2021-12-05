#ifndef _ORIGIN_LOGGER_
#define _ORIGIN_LOGGER_

// macros for robust logging
#define ORIGIN_ERROR(x)       origin::OriginLogger::CreateLogger()->error(x)
#define ORIGIN_DEBUG(x)       origin::OriginLogger::CreateLogger()->debug(x)
#define ORIGIN_INFO(x)        origin::OriginLogger::CreateLogger()->info(x)  
#define ORIGIN_BUFFER(x)      origin::OriginLogger::CreateLogger()->buffer(x)
#define ORIGIN_FATAL(x)       origin::OriginLogger::CreateLogger()->fatal(x)

namespace origin 
{
    // class declaration
    class OriginLogger
    {
        public:
            // constructor
            OriginLogger(void) { }

            // destructor
            ~OriginLogger(void) { }

            // non-static member functions
            virtual void error(const char *text)    = 0;
            virtual void error(std::string text)   = 0;

            virtual void debug(const char *text)    = 0;
            virtual void debug(std::string text)   = 0;

            virtual void info(const char *text)     = 0;
            virtual void info(std::string text)    = 0;

            virtual void buffer(const char *text)   = 0;
            virtual void buffer(std::string text)  = 0;

            virtual void fatal(const char *text)    = 0;
            virtual void fatal(std::string text)   = 0;

            // static member functions
            static OriginLogger* CreateLogger(void);
            static void DeleteLogger(void);
    };
}

#endif /* _ORIGIN_LOGGER_ */

