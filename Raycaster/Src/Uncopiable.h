#ifndef UNCOPIABLE_H__
#define UNCOPIABLE_H__

#pragma once

namespace raycaster
{
    // The Rule of Zero
    class Uncopiable
    {
    public:
        Uncopiable() = default;
        Uncopiable(Uncopiable&&) = default;
        Uncopiable(const Uncopiable&) = delete;
        Uncopiable& operator=(const Uncopiable&) = delete;
        Uncopiable& operator=(Uncopiable&&) = default;
    };
};

#endif // !UNCOPIABLE_H__