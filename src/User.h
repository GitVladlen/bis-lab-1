#pragma once

class User
{
public:
    User();
    ~User();

private:
    bool m_isAdmin;
    bool m_isLoggedIn;
};