#ifndef MENU_BASE_CXX
#define MENU_BASE_CXX

#include "menubase.hxx"

MenuBase::MenuBase()
{

}

MenuBase::~MenuBase()
{

}

bool MenuBase::Initiate()
{
    return (true);
}

void MenuBase::Cleanup()
{
}

void MenuBase::NextItem()
{
    if (current < (menuItems.size() - 1))
    {
        current++;
    } else
    {
        current = 0;
    }
}

void MenuBase::PreviousItem()
{
    if (current > 0)
    {
        current--;
    } else
    {
        current = (menuItems.size() - 1);
    }
}

#endif
