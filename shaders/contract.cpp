#include "Shaders/common.h"
#include "Shaders/app_common_impl.h"
#include "Shaders/Math.h"
#include "contract.h"

using namespace SerializationSample;

BEAM_EXPORT void Ctor(Buffer& paramsBuffer)
{
	using Str = std::vector<char>;
	Str tst;
	for (int i = 0; i < 1000; ++i)
	{
		tst.push_back('g');
	}
	InitialParams params;
	MemStream ms(paramsBuffer.data, paramsBuffer.size);
	yas::binary_iarchive<MemStream, YAS_FLAGS> iar(ms);

	iar& params;

	Env::SaveVar_T(0, params);
}

BEAM_EXPORT void Dtor(void*)
{
	Env::DelVar_T(0);
}

BEAM_EXPORT void Method_2(void*)
{

}
