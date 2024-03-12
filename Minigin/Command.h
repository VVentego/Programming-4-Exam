#ifndef COMMAND
#define COMMAND
class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};
#endif // !COMMAND