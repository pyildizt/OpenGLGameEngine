#ifndef IANIMATABLE_H
#define IANIMATABLE_H

class IAnimatable
{
public:
    virtual ~IAnimatable() = default;
    virtual void Update(float deltaTime) = 0;
};

#endif