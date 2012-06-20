#include "filter.h"

using namespace Filtering;

typedef Byte (Operator4)(Byte, Byte, Byte, Byte);
typedef Byte (Operator2)(Byte, Byte);

inline Byte o_and(Byte a, Byte b, Byte th1, Byte th2) { UNUSED(th1); UNUSED(th2); return a & b; }
inline Byte o_or(Byte a, Byte b, Byte th1, Byte th2) { UNUSED(th1); UNUSED(th2); return a | b; }
inline Byte o_andn(Byte a, Byte b, Byte th1, Byte th2) { UNUSED(th1); UNUSED(th2); return a & ~b; }
inline Byte o_xor(Byte a, Byte b, Byte th1, Byte th2) { UNUSED(th1); UNUSED(th2); return a ^ b; }
inline Byte o_add(Byte a, Byte b) { return clip<Byte, int>(a + (int)b); }
inline Byte o_sub(Byte a, Byte b) { return clip<Byte, int>(a - (int)b); }
inline Byte o_nop(Byte a, Byte b) { UNUSED(b); return a; }

template <Operator2 opa, Operator2 opb>
inline Byte min_t(Byte a, Byte b, Byte th1, Byte th2) { return min<Byte>(opa(a, th1), opb(b, th2)); }

template <Operator2 opa, Operator2 opb>
inline Byte max_t(Byte a, Byte b, Byte th1, Byte th2) { return max<Byte>(opa(a, th1), opb(b, th2)); }

template <Operator4 op>
void logic_t(Byte *pDst, ptrdiff_t nDstPitch, const Byte *pSrc, ptrdiff_t nSrcPitch, int nWidth, int nHeight, Byte nThresholdDestination, Byte nThresholdSource)
{
   for ( int y = 0; y < nHeight; y++ )
   {
      for ( int x = 0; x < nWidth; x++ )
         pDst[x] = op(pDst[x], pSrc[x], nThresholdDestination, nThresholdSource);
      pDst += nDstPitch;
      pSrc += nSrcPitch;
   }
}

namespace Filtering { namespace MaskTools { namespace Filters { namespace Logic {

Processor *and_c  = &logic_t<o_and>;
Processor *or_c   = &logic_t<o_or>;
Processor *andn_c = &logic_t<o_andn>;
Processor *xor_c  = &logic_t<o_xor>;

#define TRIPLE(left, leftop, mode) \
Processor *left##mode##_c = &logic_t<mode##_t<leftop, o_nop> >; \
Processor *left##mode##sub_c = &logic_t<mode##_t<leftop, o_sub> >; \
Processor *left##mode##add_c = &logic_t<mode##_t<leftop, o_add> >

#define NINE(mode) \
TRIPLE(,o_nop, mode); \
TRIPLE(sub,o_sub, mode); \
TRIPLE(add,o_add, mode)

NINE(min);
NINE(max);

} } } }
