#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include "item.h"

using namespace std;

class Notebook final : public Item
{
public:
    /**
     * @param subjects int
     * @param stock int
     * @param price double
     * @param name string
     * @param desc string
     */
    Notebook(int, int, double, string, string);

    void setSubjects(int);
    int  getSubjects();

    void   setId() override;
    string getDetails() override;

private:
    int _subjects;
};

#endif // NOTEBOOK_H
