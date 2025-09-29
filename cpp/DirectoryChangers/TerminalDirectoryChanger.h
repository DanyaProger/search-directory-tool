#ifndef TERMINALDIRECTORYCHANGER_H_INCLUDED
#define TERMINALDIRECTORYCHANGER_H_INCLUDED

class TerminalDirectoryChanger : public DirectoryChanger
{
private:
    int delay;
public:
    TerminalDirectoryChanger(int delay)
    {
        this.delay = delay;
    }

    int delay()
    {
        return this.delay;
    }

    virtual wstring path_to_cd_command(wstring path);

    void change_directory(wstring path) override {

    }
};

#endif // TERMINALDIRECTORYCHANGER_H_INCLUDED
