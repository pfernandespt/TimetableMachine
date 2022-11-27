//
// Created by paulo on 16/08/2022.
//

#include "Subject.h"

Subject::Subject() {
    enabled = true;
}

bool Subject::operator==(const Subject &rhs) const {
    return abbreviation == rhs.abbreviation &&
           type == rhs.type;
}

bool Subject::operator!=(const Subject &rhs) const {
    return !(rhs == *this);
}

Subject::Subject(const std::string &abbreviation, const std::string &type) : abbreviation(abbreviation), type(type) {}
