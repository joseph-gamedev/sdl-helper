#ifndef APPLICATION_H
#define APPLICATION_H

class Application {
public:
    Application();
    ~Application();

    // Initialize the application
    virtual void Initialize();

    // Run the application
    virtual void Run();

    // Shutdown the application
    virtual void Shutdown();
	
private:
    // Add any necessary member variables or methods here
};

#endif // APPLICATION_H
