// Purpose: Ensure a class has one instance and provide a global access point.
class Settings {
private:
    Settings() = default;

public:
    Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;

    static Settings& instance() {
        static Settings settings;
        return settings;
    }
};

// USAGE
Settings& a = Settings::instance();
Settings& b = Settings::instance();