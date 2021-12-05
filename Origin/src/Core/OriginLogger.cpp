// -----------------------------------------------------------------
// headers 
// -----------------------------------------------------------------

#include <Origin.h>

// -----------------------------------------------------------------
// class declaration
// -----------------------------------------------------------------

class Logger : public origin::OriginLogger
{
    private:
        std::ofstream   m_File;

        void addDateAndTime(void);

    public:
        static Logger*     m_Instance;

        // constructor
        Logger(void);

        // destructor
        ~Logger(void);

        // member functions
        void error(const char *text);
        void error(std::string text);

        void debug(const char *text);
        void debug(std::string text);

        void info(const char *text);
        void info(std::string text);

        void buffer(const char *text);
        void buffer(std::string text);

        void fatal(const char *text);
        void fatal(std::string text);

};

// -----------------------------------------------------------------
// static member definitions
// -----------------------------------------------------------------

Logger* Logger::m_Instance = 0;

// -----------------------------------------------------------------
// class definition
// -----------------------------------------------------------------

Logger::Logger(void)
{
    // code
    m_File.open("Log.txt", std::ios::out|std::ios::app);
    m_File << "---------------------------------------------------------------------------------" << std::endl;  
    
    addDateAndTime();
    m_File << "Begin Session\n" << std::endl;
}

Logger::~Logger(void)
{
    // code
    m_File << "\n";
    addDateAndTime();
    m_File << "End Session\n";
    m_File << "---------------------------------------------------------------------------------" << std::endl;
    m_File.close();
}

void Logger::error(const char *text)
{
    // variable declaration
    std::string data;

    // code
    addDateAndTime();
    data.append("ERROR  : ");
    data.append(text);
    m_File << data << std::endl;
}

void Logger::error(std::string text)
{
    // code
    error(text.data());
}

void Logger::debug(const char *text)
{
    // variable declaration
    std::string data;

    // code
    data.append("DEBUG  : ");
    data.append(text);
    m_File << data << std::endl;
}

void Logger::debug(std::string text)
{
    // code
    debug(text.data());
}

void Logger::info(const char *text)
{
    // variable declaration
    std::string data;

    // code
    addDateAndTime();
    data.append("INFO   : ");
    data.append(text);
    m_File << data << std::endl;
}   

void Logger::info(std::string text)
{
    // code
    info(text.data());
}

void Logger::buffer(const char *text)
{
    // variable declaration
    std::string data;

    // code
    data.append(text);
    m_File << data << std::endl;
}

void Logger::buffer(std::string text)
{
    // code
    m_File << text << std::endl;
}

void Logger::fatal(const char *text)
{
    // variable declaration
    std::string data;

    // code
    addDateAndTime();
    data.append("FATAL  : ");
    data.append(text);
    m_File << data << std::endl;
}

void Logger::fatal(std::string text)
{
    // code
    fatal(text.data());
}

void Logger::addDateAndTime(void)
{
    // code
    time_t now = time(0);
    tm ltm; 

    localtime_s(&ltm, &now);

    m_File << "[" << ltm.tm_mday << "-" << 1 + ltm.tm_mon << "-" << 1900 + ltm.tm_year << " | ";
    m_File << ltm.tm_hour << ":" << ltm.tm_min << ":" << ltm.tm_sec << "] ";
}

// -----------------------------------------------------------------
// Interface functions for object creation/destruction
// -----------------------------------------------------------------

origin::OriginLogger* origin::OriginLogger::CreateLogger(void)
{
    // code
    if(Logger::m_Instance == 0)
    {
        Logger::m_Instance = new Logger();
    }

    return (Logger::m_Instance);
}

void origin::OriginLogger::DeleteLogger(void)
{
    // code
    delete (Logger::m_Instance);
}

