#ifndef COLOR_GROUP_HPP
#define COLOR_GROUP_HPP

#include <vector>
#include <string>

class StreetSquare;

class ColorGroup {
private:
    std::string color;
    std::vector<StreetSquare*> properties;
    int maxProperties;

public:
    ColorGroup(const std::string& color, int maxProperties);
    
    void addProperty(StreetSquare* property);
    bool hasMonopoly() const;
    bool hasEvenDevelopment(const StreetSquare& property) const;
    
    std::string getColor() const { return color; }
    const std::vector<StreetSquare*>& getProperties() const { return properties; }
};

#endif // COLOR_GROUP_HPP