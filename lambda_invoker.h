#include <cstring>
class Functor {
public:
	void operator()(){};
};

template<std::size_t MemAmount = 8, typename Type = Functor>
class Invoker {
	uint8_t mem[MemAmount] = {0};
public:
	template<typename Lambda>
	Invoker(Lambda&& lbd) {
		std::memcpy(mem, &lbd, sizeof(lbd));
	}

	template<typename ... Args>
	auto operator()(Args... args) {
		return (*(Type*)(mem)).operator()(std::forward<Args>(args)...);
	}
};

template<typename Lambda>
Invoker(Lambda&& lbd)->Invoker<sizeof(Lambda), Lambda>;
