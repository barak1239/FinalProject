//every street square has to have a colorgroup for tracking monopolies, this implements the colorgroup + functions
#include "color_group.hpp"
#include "street_square.hpp"

ColorGroup::ColorGroup(const std::string& color, int maxProperties)
    : color(color), maxProperties(maxProperties) {}

void ColorGroup::addProperty(StreetSquare* property) {
    if (properties.size() < static_cast<size_t>(maxProperties)) {
        properties.push_back(property);
    }
}

bool ColorGroup::hasMonopoly() const {
    return properties.size() == static_cast<size_t>(maxProperties);
}

bool ColorGroup::hasEvenDevelopment(const StreetSquare& property) const {
    int propertyHouses = property.getHouseCount();
    for (const auto& p : properties) {
        if (p->getHouseCount() < propertyHouses - 1 || p->getHouseCount() > propertyHouses) {
            return false;
        }
    }
    return true;
}