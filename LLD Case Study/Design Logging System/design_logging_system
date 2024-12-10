# Low-Level Design for a Logging System
    
## Overview
A Logging System records events and system behavior during application execution. It is vital for monitoring, debugging, and auditing in software systems. The logging system supports different logging levels (INFO, DEBUG, WARN, ERROR), multiple outputs (console, file, database), and ensures scalability for high-volume logging in distributed environments.

---

## System Requirements
1. <strong>Log Levels</strong>: Support for levels like INFO, DEBUG, WARN, and ERROR.
2. <strong>Multi-output Support</strong>: Logs can be sent to consoles, files, or databases.
3. <strong>Asynchronous Logging</strong>: Log processing should not block application execution.
4. <strong>Format Customization</strong>: Support custom log formats (e.g., JSON, plaintext).
5. <strong>Rotation and Archiving</strong>: Rotate and archive logs based on size or time.
6. <strong>Filter by Levels</strong>: Allow filtering logs by severity.
7. <strong>Searchable Logs</strong>: Enable searching of logs via keywords or time range.
8. <strong>Error Alerts</strong>: Notify stakeholders when critical errors occur.
9. <strong>Thread-safe Logging</strong>: Ensure thread safety in multi-threaded applications.
10. <strong>Log Configuration</strong>: Runtime configuration of log levels and outputs.
11. <strong>Support for Contextual Information</strong>: Add metadata like timestamps, thread IDs, and source modules.
12. <strong>Scalability</strong>: Handle high-frequency logging in distributed systems.
13. <strong>Persistence</strong>: Store logs in durable storage for auditing purposes.
14. <strong>Extensibility</strong>: Add new log output types without altering the core design.
15. <strong>Reliability</strong>: Ensure log delivery without data loss.

---

## Class Diagram

``` plaintext

+---------------------+
|       Logger        |
+---------------------+
| - instance          |
| - logLevel          |
| - outputs[]         |
| + getInstance()     |
| + log(level, msg)   |
+---------------------+
          |
          v
+---------------------+
|   LogOutput (IF)    |
+---------------------+
| + write(log)        |
+---------------------+
          |
          |
+-------------------+    +--------------------+   +--------------------+
| ConsoleOutput     |    |  FileOutput        |   | DatabaseOutput     |
+-------------------+    +--------------------+   +--------------------+
| + write(log)      |    | + write(log)       |   | + write(log)       |
+-------------------+    +--------------------+   +--------------------+

+---------------------+
|       LogEntry      |
+---------------------+
| - timestamp         |
| - level             |
| - message           |
| + format()          |
+---------------------+
```

### Explanation:

1. <strong>Logger</strong>: Central class following Singleton Pattern for a single logging instance.
2. <strong>LogOutput (Interface)</strong>: Defines a method for log outputs.
3. <strong>ConsoleOutput, FileOutput, DatabaseOutput</strong>: Implementations of LogOutput.
4. <strong>LogEntry</strong>: Represents an individual log entry.

### Relationships:

* `Logger` uses multiple `LogOutput` implementations.
* `LogEntry` is the data model for logs passed to `LogOutput`.

---

## Use Case Diagram

``` plaintext

+----------------+
|     User       |
+----------------+
        |
        v
+----------------+
|   Log Message  |
+----------------+
        |
+----------------+
| Filter by Level|
+----------------+
        |
+----------------+
| Write to Output|
+----------------+
```
### Use Cases:

1. <strong>Log Message</strong>: User logs a message with a specific level.
2. <strong>Filter by Level</strong>: Logs are filtered by the set level.
3. <strong>Write to Output</strong>: Logs are written to one or more outputs.

---

## Schema Diagram
```plaintext

+---------------------+
|       LogEntry      |
+---------------------+
| logId (PK)          |
| timestamp           |
| level               |
| message             |
+---------------------+
```
### Cardinality:

A Logger can generate multiple LogEntries.

---

## Activity Diagram
``` plaintext

+----------------------+
| Start Logging Request|
+----------------------+
             |
+----------------------+
| Check Log Level      |
+----------------------+
             |
+----------------------+
| Format Log Message   |
+----------------------+
             |
+----------------------+
| Write to Outputs     |
+----------------------+
             |
+----------------------+
| End Logging Request  |
+----------------------+
```
---

## Design Patterns
1. <strong>Singleton Pattern</strong>:
Ensures a single instance of `Logger`.

2. <strong>Strategy Pattern</strong>:
Encapsulates different logging outputs (console, file, database).

3. <strong>Observer Pattern</strong>:
Notifies multiple outputs when a log is generated.

---

## C++ Code

``` cpp

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <mutex>

// Enum for log levels
enum LogLevel { INFO, DEBUG, WARN, ERROR };

// LogEntry Class
class LogEntry {
private:
    std::string timestamp;
    LogLevel level;
    std::string message;

public:
    LogEntry(const std::string& time, LogLevel lvl, const std::string& msg)
        : timestamp(time), level(lvl), message(msg) {}

    std::string format() const {
        return "[" + timestamp + "] " + std::to_string(level) + ": " + message;
    }
};

// LogOutput Interface
class LogOutput {
public:
    virtual void write(const LogEntry& entry) = 0;
    virtual ~LogOutput() {}
};

// ConsoleOutput Class
class ConsoleOutput : public LogOutput {
public:
    void write(const LogEntry& entry) override {
        std::cout << entry.format() << std::endl;
    }
};

// Singleton Logger Class
class Logger {
private:
    static Logger* instance;
    static std::mutex mutex_;
    LogLevel currentLevel;
    std::vector<std::shared_ptr<LogOutput>> outputs;

    Logger() : currentLevel(INFO) {}

public:
    static Logger* getInstance() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance) {
            instance = new Logger();
        }
        return instance;
    }

    void setLogLevel(LogLevel level) {
        currentLevel = level;
    }

    void addOutput(std::shared_ptr<LogOutput> output) {
        outputs.push_back(output);
    }

    void log(LogLevel level, const std::string& message) {
        if (level >= currentLevel) {
            LogEntry entry("2024-10-13", level, message); // Example timestamp
            for (auto& output : outputs) {
                output->write(entry);
            }
        }
    }
};

Logger* Logger::instance = nullptr;
std::mutex Logger::mutex_;

int main() {
    // Get Logger Instance
    Logger* logger = Logger::getInstance();
    logger->setLogLevel(INFO);

    // Add Console Output
    logger->addOutput(std::make_shared<ConsoleOutput>());

    // Log Messages
    logger->log(INFO, "System initialized.");
    logger->log(ERROR, "Critical error occurred!");

    return 0;
}
```
---

## S.O.L.I.D. Principles
1. <strong>SRP</strong>: Each class has a single responsibility (e.g., `Logger` handles log management, `LogOutput` handles writing logs).
2. <strong>OCP</strong>: New log output types can be added without modifying the existing code.
3. <strong>LSP</strong>: `ConsoleOutput`, `FileOutput`, etc., can replace `LogOutput` without breaking functionality.
4. <strong>ISP</strong>: `LogOutput` provides a simple interface with only necessary methods.
5. <strong>DIP</strong>: Logger depends on the abstraction `LogOutput`, not concrete implementations.