#include <sys/types.h>
#include <sys/stat.h>
#include "IOperand.hpp"
#include "Operand.hpp"
#include "Factory.hpp"
#include "VM.hpp"

struct stat info;

int main(int argc, const char **argv)
{
	std::ifstream	ifs;

	if (argc > 1) {
		try {
			stat(argv[1], &info);
			if (info.st_mode & S_IFDIR)
				throw std::runtime_error("Is a directory");
			ifs.open(argv[1], std::ifstream::in);
			if (ifs.is_open()) {
				VM(ifs).read();
				ifs.close();
			} else throw std::runtime_error("Can't open file");
		} catch (const std::exception & e) {
			std::cerr << "Error : " << e.what() << " : " << argv[1] << std::endl;
			return (-1);
		}
	} else
		VM().read();
	return (0);
}
