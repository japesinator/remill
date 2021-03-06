/* Copyright 2016 Akshay Kumar (iit.akshay@gmail.com), all rights reserved. */

#ifndef REMILL_ARCH_X86_SEMANTICS_MMX_H_
#define REMILL_ARCH_X86_SEMANTICS_MMX_H_

namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(PUNPCKHBW, D dst, S1 src1, S2 src2) {
  auto src1_vec = UReadV8(src1);
  auto src2_vec = UReadV8(src2);
  auto dst_vec = UClearV8(UReadV8(dst));
  auto num_elems = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0, j = num_elems; i < (num_elems / 2); ++i, j -= 2) {
    dst_vec = UInsertV8(
        dst_vec, j - 1, UExtractV8(src2_vec, (num_elems-1) - i));
    dst_vec = UInsertV8(
        dst_vec, j - 2, UExtractV8(src1_vec, (num_elems-1) - i));
  }
  UWriteV8(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PUNPCKHWD, D dst, S1 src1, S2 src2) {
  auto src1_vec = UReadV16(src1);
  auto src2_vec = UReadV16(src2);
  auto dst_vec = UClearV16(UReadV16(dst));
  auto num_elems = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0, j = num_elems; i < (num_elems / 2); ++i, j -= 2) {
    dst_vec = UInsertV16(
        dst_vec, j - 1, UExtractV16(src2_vec, (num_elems-1) - i));
    dst_vec = UInsertV16(
        dst_vec, j - 2, UExtractV16(src1_vec, (num_elems-1) - i));
  }
  UWriteV16(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PUNPCKHDQ, D dst, S1 src1, S2 src2) {
  auto src1_vec = UReadV32(src1);
  auto src2_vec = UReadV32(src2);
  auto dst_vec = UClearV32(UReadV32(dst));
  auto num_elems = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0, j = num_elems; i < (num_elems / 2); ++i, j -= 2) {
    dst_vec = UInsertV32(
        dst_vec, j - 1, UExtractV32(src2_vec, (num_elems-1) - i));
    dst_vec = UInsertV32(
        dst_vec, j - 2, UExtractV32(src1_vec, (num_elems-1) - i));
  }
  UWriteV32(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PUNPCKLBW, D dst, S1 src1, S2 src2) {
  auto src1_vec = UReadV8(src1);
  auto src2_vec = UReadV8(src2);
  auto dst_vec = UClearV8(UReadV8(dst));
  auto num_elems = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0, j = 0; i < (num_elems / 2); ++i, j += 2) {
    dst_vec = UInsertV8(dst_vec, j, UExtractV8(src1_vec, i));
    dst_vec = UInsertV8(dst_vec, j+1, UExtractV8(src2_vec, i));
  }
  UWriteV8(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PUNPCKLWD, D dst, S1 src1, S2 src2) {
  auto src1_vec = UReadV16(src1);
  auto src2_vec = UReadV16(src2);
  auto dst_vec = UClearV16(UReadV16(dst));
  auto num_elems = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0, j = 0; i < (num_elems / 2); ++i, j += 2) {
    dst_vec = UInsertV16(dst_vec, j, UExtractV16(src1_vec, i));
    dst_vec = UInsertV16(dst_vec, j+1, UExtractV16(src2_vec, i));
  }
  UWriteV16(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PUNPCKLDQ, D dst, S1 src1, S2 src2) {
  auto src1_vec = UReadV32(src1);
  auto src2_vec = UReadV32(src2);
  auto dst_vec = UClearV32(UReadV32(dst));
  auto num_elems = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0, j = 0; i < (num_elems / 2); ++i, j += 2) {
    dst_vec = UInsertV32(dst_vec, j, UExtractV32(src1_vec, i));
    dst_vec = UInsertV32(dst_vec, j + 1, UExtractV32(src2_vec, i));
  }
  UWriteV32(dst, dst_vec);
}

}  // namespace

DEF_ISEL(PUNPCKHBW_MMXq_MEMq) = PUNPCKHBW<V64W, V64, MV64>;
DEF_ISEL(PUNPCKHBW_MMXq_MMXd) = PUNPCKHBW<V64W, V64, V64>;
DEF_ISEL(PUNPCKHWD_MMXq_MEMq) = PUNPCKHWD<V64W, V64, MV64>;
DEF_ISEL(PUNPCKHWD_MMXq_MMXd) = PUNPCKHWD<V64W, V64, V64>;
DEF_ISEL(PUNPCKHDQ_MMXq_MEMq) = PUNPCKHDQ<V64W, V64, MV64>;
DEF_ISEL(PUNPCKHDQ_MMXq_MMXd) = PUNPCKHDQ<V64W, V64, V64>;
DEF_ISEL(PUNPCKLBW_MMXq_MEMd) = PUNPCKLBW<V64W, V64, MV64>;
DEF_ISEL(PUNPCKLBW_MMXq_MMXd) = PUNPCKLBW<V64W, V64, V64>;
DEF_ISEL(PUNPCKLWD_MMXq_MEMd) = PUNPCKLWD<V64W, V64, MV64>;
DEF_ISEL(PUNPCKLWD_MMXq_MMXd) = PUNPCKLWD<V64W, V64, V64>;
DEF_ISEL(PUNPCKLDQ_MMXq_MEMd) = PUNPCKLDQ<V64W, V64, MV64>;
DEF_ISEL(PUNPCKLDQ_MMXq_MMXd) = PUNPCKLDQ<V64W, V64, V64>;


// Adding new MMX Instructions
namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(PADDB, D dst, S1 src1, S2 src2) {
  auto lhs_vec = UReadV8(src1);
  auto rhs_vec = UReadV8(src2);
  auto dst_vec = UAddV8(lhs_vec, rhs_vec);
  UWriteV8(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PADDW, D dst, S1 src1, S2 src2) {
  auto lhs_vec = UReadV16(src1);
  auto rhs_vec = UReadV16(src2);
  auto dst_vec = UAddV16(lhs_vec, rhs_vec);
  UWriteV16(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PADDD, D dst, S1 src1, S2 src2) {
  auto lhs_vec = UReadV32(src1);
  auto rhs_vec = UReadV32(src2);
  auto dst_vec = UAddV32(lhs_vec, rhs_vec);
  UWriteV32(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PADDQ, D dst, S1 src1, S2 src2) {
  auto lhs_vec = UReadV64(src1);
  auto rhs_vec = UReadV64(src2);
  auto dst_vec = UAddV64(lhs_vec, rhs_vec);
  UWriteV64(dst, dst_vec);
}

}  // namespace

DEF_ISEL(PADDB_MMXq_MMXq) = PADDB<V64W, V64, V64>;
DEF_ISEL(PADDB_MMXq_MEMq) = PADDB<V64W, V64, MV64>;

DEF_ISEL(PADDW_MMXq_MMXq) = PADDW<V64W, V64, V64>;
DEF_ISEL(PADDW_MMXq_MEMq) = PADDW<V64W, V64, MV64>;

DEF_ISEL(PADDD_MMXq_MMXq) = PADDD<V64W, V64, V64>;
DEF_ISEL(PADDD_MMXq_MEMq) = PADDD<V64W, V64, MV64>;

DEF_ISEL(PADDQ_MMXq_MMXq) = PADDQ<V64W, V64, V64>;
DEF_ISEL(PADDQ_MMXq_MEMq) = PADDQ<V64W, V64, MV64>;

/*
 * signed saturation arithematic for PADDS
 * int8 res = a + b;
 * int8 tmp = (res & ~(a | b)) < 0 ? 0x7f : res;
 * int8 c = (~res & (a & b)) < 0 ? 0x80 : tmp;
 *
 */

namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(PADDSB, D dst, S1 src1, S2 src2) {
  auto src1_vec = SReadV8(src1);
  auto src2_vec = SReadV8(src2);
  auto dst_vec = SClearV8(SReadV8(dst));

  // Compute signed saturation arithematic on each bytes
  _Pragma("unroll")
  for (size_t index = 0; index < NumVectorElems(src1_vec); index++) {
    auto v1 = SExtractV8(src1_vec, index);
    auto v2 = SExtractV8(src2_vec, index);
    auto max = SExt(Maximize(v1));
    auto min = SExt(Minimize(v1));
    auto sum = SAdd(SExt(v1), SExt(v2));
    auto upper_limit = Select(SCmpLt(sum, max), sum, max);
    auto lower_limit = Select(SCmpGte(sum, min), sum, min);
    sum = Select(SCmpLt(sum, decltype(sum)(0)), lower_limit, upper_limit);
    dst_vec = SInsertV8(dst_vec, index, Trunc(sum));
  }
  SWriteV8(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PADDSW, D dst, S1 src1, S2 src2) {
  auto src1_vec = SReadV16(src1);
  auto src2_vec = SReadV16(src2);

  // Compute signed saturation arithematic on each bytes
  auto dst_vec = SClearV16(SReadV16(dst));
  _Pragma("unroll")
  for (size_t index = 0; index < NumVectorElems(src1_vec); index++) {
    auto v1 = SExtractV16(src1_vec, index);
    auto v2 = SExtractV16(src2_vec, index);
    auto max = SExt(Maximize(v1));
    auto min = SExt(Minimize(v1));
    auto sum = SAdd(SExt(v1), SExt(v2));
    auto upper_limit = Select(SCmpLt(sum, max), sum, max);
    auto lower_limit = Select(SCmpGte(sum, min), sum, min);
    sum = Select(SCmpLt(sum, decltype(sum)(0)), lower_limit, upper_limit);
    dst_vec = SInsertV16(dst_vec, index, Trunc(sum));
  }
  SWriteV16(dst, dst_vec);
}
}  // namespace

DEF_ISEL(PADDSB_MMXq_MMXq) = PADDSB<V64W, V64, V64>;
DEF_ISEL(PADDSB_MMXq_MEMq) = PADDSB<V64W, V64, MV64>;

DEF_ISEL(PADDSW_MMXq_MMXq) = PADDSW<V64W, V64, V64>;
DEF_ISEL(PADDSW_MMXq_MEMq) = PADDSW<V64W, V64, MV64>;

namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(PHADDW, D dst, S1 src1, S2 src2) {
  auto lhs_vec = SReadV16(src1);
  auto rhs_vec = SReadV16(src2);
  auto dst_vec = SClearV16(SReadV16(dst));

  // Compute the horizontal packing
  auto vec_count = NumVectorElems(lhs_vec);
  _Pragma("unroll")
  for (size_t index = 0; index < vec_count; index += 2) {
    auto v1 = SExtractV16(lhs_vec, index);
    auto v2 = SExtractV16(lhs_vec, index+1);
    auto i = UDiv(index, 2);
    dst_vec = SInsertV16(dst_vec, i, SAdd(v1, v2));
  }
  _Pragma("unroll")
  for (size_t index = 0; index < NumVectorElems(rhs_vec); index += 2) {
    auto v1 = SExtractV16(rhs_vec, index);
    auto v2 = SExtractV16(rhs_vec, index+1);
    auto i = UAdd(index, vec_count);
    i = UDiv(i, 2);
    dst_vec = SInsertV16(dst_vec, i, SAdd(v1, v2));
  }
  SWriteV16(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PHADDD, D dst, S1 src1, S2 src2) {
  auto lhs_vec = SReadV32(src1);
  auto rhs_vec = SReadV32(src2);
  auto dst_vec = SClearV32(SReadV32(dst));

  // Compute the horizontal packing
  auto vec_count = NumVectorElems(lhs_vec);
  _Pragma("unroll")
  for (size_t index = 0; index < vec_count; index += 2) {
    auto v1 = SExtractV32(lhs_vec, index);
    auto v2 = SExtractV32(lhs_vec, index+1);
    auto i = UDiv(index, 2);
    dst_vec = SInsertV32(dst_vec, i, SAdd(v1, v2));
  }
  _Pragma("unroll")
  for (size_t index = 0; index < NumVectorElems(rhs_vec); index += 2) {
    auto v1 = SExtractV32(rhs_vec, index);
    auto v2 = SExtractV32(rhs_vec, index+1);
    auto i = UDiv(UAdd(index, vec_count), 2);
    dst_vec = SInsertV32(dst_vec, i, SAdd(v1, v2));
  }
  SWriteV32(dst, dst_vec);
}

}  // namespace

DEF_ISEL(PHADDW_MMXq_MMXq) = PHADDW<V64W, V64, V64>;
DEF_ISEL(PHADDW_MMXq_MEMq) = PHADDW<V64W, V64, MV64>;

DEF_ISEL(PHADDD_MMXq_MMXq) = PHADDD<V64W, V64, V64>;
DEF_ISEL(PHADDD_MMXq_MEMq) = PHADDD<V64W, V64, MV64>;

template <typename D, typename S1, typename S2>
DEF_SEM(PHADDSW, D dst, S1 src1, S2 src2) {
  auto src1_vec = SReadV16(src1);
  auto src2_vec = SReadV16(src2);
  auto dst_vec = SClearV16(SReadV16(dst));

  auto vec_count = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t index = 0; index < vec_count; index += 2) {
    auto add_elem = SAdd(SExtractV16(src1_vec, index),
                         SExtractV16(src1_vec, index+1));
    auto or_elem = SOr(SExtractV16(src1_vec, index),
                       SExtractV16(src1_vec, index+1));
    auto and_elem = SAnd(SExtractV16(src1_vec, index),
                         SExtractV16(src1_vec, index+1));
    auto tmp = Select(
        SCmpLt(SAnd(add_elem, SNot(or_elem)), decltype(add_elem)(0)),
        Maximize(add_elem),
        add_elem);
    auto value = Select(
        SCmpLt(SAnd(SNot(add_elem), and_elem), decltype(add_elem)(0)),
        decltype(add_elem)(0x8000),
        tmp);
    dst_vec = SInsertV16(dst_vec, index/2, value);
  }

  _Pragma("unroll")
  for (size_t index = 0; index < NumVectorElems(src2_vec); index += 2) {
    auto add_elem = SAdd(SExtractV16(src2_vec, index),
                         SExtractV16(src2_vec, index+1));
    auto or_elem = SOr(SExtractV16(src2_vec, index),
                       SExtractV16(src2_vec, index+1));
    auto and_elem = SAnd(SExtractV16(src2_vec, index),
                         SExtractV16(src2_vec, index+1));
    auto tmp = Select(
        SCmpLt(SAnd(add_elem, SNot(or_elem)), decltype(add_elem)(0)),
        Maximize(add_elem),
        add_elem);
    auto value = Select(
        SCmpLt(SAnd(SNot(add_elem), and_elem), decltype(add_elem)(0)),
        decltype(add_elem)(0x8000),
        tmp);
    dst_vec = SInsertV16(dst_vec, (index+vec_count)/2, value);
  }
  SWriteV16(dst, dst_vec);
}

DEF_ISEL(PHADDSW_MMXq_MMXq) = PHADDSW<V64W, V64, V64>;
DEF_ISEL(PHADDSW_MMXq_MEMq) = PHADDSW<V64W, V64, MV64>;

namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(PSUBB, D dst, S1 src1, S2 src2) {
  auto lhs_vec = SReadV8(src1);
  auto rhs_vec = SReadV8(src2);
  auto dst_vec = SSubV8(lhs_vec, rhs_vec);
  SWriteV8(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PSUBW, D dst, S1 src1, S2 src2) {
  auto lhs_vec = SReadV16(src1);
  auto rhs_vec = SReadV16(src2);
  auto dst_vec = SSubV16(lhs_vec, rhs_vec);
  SWriteV16(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PSUBD, D dst, S1 src1, S2 src2) {
  auto lhs_vec = SReadV32(src1);
  auto rhs_vec = SReadV32(src2);
  auto dst_vec = SSubV32(lhs_vec, rhs_vec);
  SWriteV32(dst, dst_vec);
}

}  // namespace

DEF_ISEL(PSUBB_MMXq_MMXq) = PSUBB<V64W, V64, V64>;
DEF_ISEL(PSUBB_MMXq_MEMq) = PSUBB<V64W, V64, MV64>;

DEF_ISEL(PSUBW_MMXq_MMXq) = PSUBW<V64W, V64, V64>;
DEF_ISEL(PSUBW_MMXq_MEMq) = PSUBW<V64W, V64, MV64>;

DEF_ISEL(PSUBD_MMXq_MMXq) = PSUBD<V64W, V64, V64>;
DEF_ISEL(PSUBD_MMXq_MEMq) = PSUBD<V64W, V64, MV64>;

namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(PSUBUSB, D dst, S1 src1, S2 src2) {
  auto lhs_vec = UReadV8(src1);
  auto rhs_vec = UReadV8(src2);
  auto dst_vec = UClearV8(UReadV8(dst));

  _Pragma("unroll")
  for (size_t i = 0; i < NumVectorElems(dst_vec); i++) {
    auto v1 = UExtractV8(lhs_vec, i);
    auto v2 = UExtractV8(rhs_vec, i);
    auto sub = USub(v1, v2);
    auto sub_val = Select(UCmpGt(v1, v2), sub, Minimize(v1));
    dst_vec = UInsertV8(dst_vec, i, sub_val);
  }
  UWriteV8(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PSUBUSW, D dst, S1 src1, S2 src2) {
  auto lhs_vec = UReadV16(src1);
  auto rhs_vec = UReadV16(src2);
  auto dst_vec = UClearV16(UReadV16(dst));

  _Pragma("unroll")
  for (size_t i = 0; i < NumVectorElems(dst_vec); i++) {
    auto v1 = UExtractV16(lhs_vec, i);
    auto v2 = UExtractV16(rhs_vec, i);
    auto sub = USub(v1, v2);
    auto sub_val = Select(UCmpGt(v1, v2), sub, Minimize(v1));
    dst_vec = UInsertV16(dst_vec, i, sub_val);
  }
  UWriteV16(dst, dst_vec);
}

}  // namespace

DEF_ISEL(PSUBUSB_MMXq_MMXq) = PSUBUSB<V64W, V64, V64>;
DEF_ISEL(PSUBUSB_MMXq_MEMq) = PSUBUSB<V64W, V64, MV64>;

DEF_ISEL(PSUBUSW_MMXq_MMXq) = PSUBUSW<V64W, V64, V64>;
DEF_ISEL(PSUBUSW_MMXq_MEMq) = PSUBUSW<V64W, V64, MV64>;

namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(PAVGB, D dst, S1 src1, S2 src2) {
  auto lhs_vec = UReadV8(src1);
  auto rhs_vec = UReadV8(src2);
  auto dst_vec = UClearV8(UReadV8(dst));

  // Compute the AVG; The sum can spill to 9th bits
  auto vec_count = NumVectorElems(lhs_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = UExtractV8(lhs_vec, i);
    auto v2 = UExtractV8(rhs_vec, i);
    auto sum_elem = UAdd(ZExt(v1), ZExt(v2));
    auto sum = UAdd(sum_elem, decltype(sum_elem)(1));
    dst_vec = UInsertV8(dst_vec, i, UInt8(UShr(sum, decltype(sum)(1))));
  }
  UWriteV8(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PAVGW, D dst, S1 src1, S2 src2) {
  auto lhs_vec = UReadV16(src1);
  auto rhs_vec = UReadV16(src2);
  auto dst_vec = UClearV16(UReadV16(dst));

  // Compute the AVG; The sum can spill to 17th bits
  auto vec_count = NumVectorElems(lhs_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = ZExt(UExtractV16(lhs_vec, i));
    auto v2 = ZExt(UExtractV16(rhs_vec, i));
    auto sum_elem = UAdd(v1, v2);
    auto sum = UAdd(sum_elem, decltype(sum_elem)(1));
    dst_vec = UInsertV16(dst_vec, i, Trunc(UShr(sum, decltype(sum)(1))));
  }
  UWriteV16(dst, dst_vec);
}

}  // namespace

DEF_ISEL(PAVGB_MMXq_MMXq) = PAVGB<V64W, V64, V64>;
DEF_ISEL(PAVGB_MMXq_MEMq) = PAVGB<V64W, V64, MV64>;

DEF_ISEL(PAVGW_MMXq_MMXq) = PAVGW<V64W, V64, V64>;
DEF_ISEL(PAVGW_MMXq_MEMq) = PAVGW<V64W, V64, MV64>;

namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(PHSUBW, D dst, S1 src1, S2 src2) {
  auto lhs_vec = SReadV16(src1);
  auto rhs_vec = SReadV16(src2);
  auto dst_vec = SClearV16(SReadV16(dst));
  auto vec_count = NumVectorElems(lhs_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i = i+2) {
    auto v1 = SExtractV16(lhs_vec, i);
    auto v2 = SExtractV16(lhs_vec, i+1);
    auto index = UDiv(i, 2);
    dst_vec = SInsertV16(dst_vec, index, SSub(v1, v2));
  }
  _Pragma("unroll")
  for (size_t i = 0; i < NumVectorElems(rhs_vec); i = i+2) {
    auto v1 = SExtractV16(rhs_vec, i);
    auto v2 = SExtractV16(rhs_vec, i+1);
    auto index = UDiv(UAdd(i, vec_count), 2);
    dst_vec = SInsertV16(dst_vec, index, SSub(v1, v2));
  }
  SWriteV16(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PHSUBD, D dst, S1 src1, S2 src2) {
  auto lhs_vec = SReadV32(src1);
  auto rhs_vec = SReadV32(src2);
  auto dst_vec = SClearV32(SReadV32(dst));
  auto vec_count = NumVectorElems(lhs_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i = i+2) {
    dst_vec = SInsertV32(
        dst_vec,
        i/2,
        SSub(SExtractV32(lhs_vec, i),
             SExtractV32(lhs_vec, i+1)));
  }
  _Pragma("unroll")
  for (size_t i = 0; i < NumVectorElems(rhs_vec); i = i+2) {
    dst_vec = SInsertV32(
        dst_vec,
        (i+vec_count)/2,
        SSub(SExtractV32(rhs_vec, i),
             SExtractV32(rhs_vec, i+1)));
  }
  SWriteV32(dst, dst_vec);
}

}  // namespace

DEF_ISEL(PHSUBW_MMXq_MMXq) = PHSUBW<V64W, V64, V64>;
DEF_ISEL(PHSUBW_MMXq_MEMq) = PHSUBW<V64W, V64, MV64>;

DEF_ISEL(PHSUBD_MMXq_MMXq) = PHSUBD<V64W, V64, V64>;
DEF_ISEL(PHSUBD_MMXq_MEMq) = PHSUBD<V64W, V64, MV64>;

namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(PMAXSW, D dst, S1 src1, S2 src2) {
  auto lhs_vec = SReadV16(src1);
  auto rhs_vec = SReadV16(src2);
  auto dst_vec = SClearV16(SReadV16(dst));

    // Compute MAX of words
  auto vec_count = NumVectorElems(lhs_vec);
  for (size_t i = 0; i < vec_count; i++) {
    auto max = Select(
        SCmpGt(SExtractV16(lhs_vec, i), SExtractV16(rhs_vec, i)),
        SExtractV16(lhs_vec, i),
        SExtractV16(rhs_vec, i));
    dst_vec = SInsertV16(dst_vec, i, max);
  }
  SWriteV16(dst, dst_vec);
}

}  // namespace

DEF_ISEL(PMAXSW_MMXq_MMXq) = PMAXSW<V64W, V64, V64>;
DEF_ISEL(PMAXSW_MMXq_MEMq) = PMAXSW<V64W, V64, MV64>;

namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(PMAXUB, D dst, S1 src1, S2 src2) {
  auto lhs_vec = UReadV8(src1);
  auto rhs_vec = UReadV8(src2);
  auto dst_vec = UClearV8(UReadV8(dst));

  // Compute MAX of bytes
  auto vec_count = NumVectorElems(lhs_vec);
  for (size_t i = 0; i < vec_count; i++) {
    auto max = Select(
        UCmpGt(UExtractV8(lhs_vec, i), UExtractV8(rhs_vec, i)),
        UExtractV8(lhs_vec, i),
        UExtractV8(rhs_vec, i));
    dst_vec = UInsertV8(dst_vec, i, max);
  }
  UWriteV8(dst, dst_vec);
}

}  // namespace

DEF_ISEL(PMAXUB_MMXq_MMXq) = PMAXUB<V64W, V64, V64>;
DEF_ISEL(PMAXUB_MMXq_MEMq) = PMAXUB<V64W, V64, MV64>;

namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(PMINSW, D dst, S1 src1, S2 src2) {
  auto lhs_vec = SReadV16(src1);
  auto rhs_vec = SReadV16(src2);
  auto dst_vec = SClearV16(SReadV16(dst));

  // Compute MIN of words
  auto vec_count = NumVectorElems(lhs_vec);
  for (size_t i = 0; i < vec_count; i++) {
    auto max = Select(
        SCmpLt(SExtractV16(lhs_vec, i), SExtractV16(rhs_vec, i)),
        SExtractV16(lhs_vec, i),
        SExtractV16(rhs_vec, i));
    dst_vec = SInsertV16(dst_vec, i, max);
  }
  SWriteV16(dst, dst_vec);
}

}  // namespace

DEF_ISEL(PMINSW_MMXq_MMXq) = PMINSW<V64W, V64, V64>;
DEF_ISEL(PMINSW_MMXq_MEMq) = PMINSW<V64W, V64, MV64>;

namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(PMINUB, D dst, S1 src1, S2 src2) {
  auto lhs_vec = UReadV8(src1);
  auto rhs_vec = UReadV8(src2);
  auto dst_vec = UClearV8(UReadV8(dst));

  // Compute MIN of bytes
  auto vec_count = NumVectorElems(lhs_vec);
  for (size_t i = 0; i < vec_count; i++) {
    auto max = Select(
        UCmpLt(UExtractV8(lhs_vec, i), UExtractV8(rhs_vec, i)),
        UExtractV8(lhs_vec, i),
        UExtractV8(rhs_vec, i));
    dst_vec = UInsertV8(dst_vec, i, max);
  }
  UWriteV8(dst, dst_vec);
}

}  // namespace

DEF_ISEL(PMINUB_MMXq_MMXq) = PMINUB<V64W, V64, V64>;
DEF_ISEL(PMINUB_MMXq_MEMq) = PMINUB<V64W, V64, MV64>;

namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(PMULHRSW, D dst, S1 src1, S2 src2) {
  auto lhs_vec = SReadV16(src1);
  auto rhs_vec = SReadV16(src2);
  auto dst_vec = SClearV16(SReadV16(dst));
  auto vec_count = NumVectorElems(lhs_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto mul = SMul(Int32(SExtractV16(lhs_vec, i)),
                    Int32(SExtractV16(rhs_vec, i)));
    auto temp = SAdd(SShr(mul, decltype(mul)(14)), decltype(mul)(1));
    temp = SShr(temp, decltype(temp)(1));
    dst_vec = SInsertV16(dst_vec, i, Int16(temp));
  }
  SWriteV16(dst, dst_vec);
}

}  // namespace

DEF_ISEL(PMULHRSW_MMXq_MMXq) = PMULHRSW<V64W, V64, V64>;
DEF_ISEL(PMULHRSW_MMXq_MEMq) = PMULHRSW<V64W, V64, MV64>;

namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(PMADDWD, D dst, S1 src1, S2 src2) {
  auto lhs_vec = SReadV16(src1);
  auto rhs_vec = SReadV16(src2);
  auto dst_vec = SClearV32(SReadV32(dst));

  // Multiply and Add Packed Integers
  auto vec_count = NumVectorElems(lhs_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i += 2) {
    auto mul1 = SMul(Int32(SExtractV16(lhs_vec, i)),
                     Int32(SExtractV16(rhs_vec, i)));
    auto mul2 = SMul(Int32(SExtractV16(lhs_vec, i+1)),
                     Int32(SExtractV16(rhs_vec, i+1)));
    dst_vec = SInsertV32(dst_vec, i/2, SAdd(mul1, mul2));
  }
  SWriteV32(dst, dst_vec);
}

}  // namespace

DEF_ISEL(PMADDWD_MMXq_MMXq) = PMADDWD<V64W, V64, V64>;
DEF_ISEL(PMADDWD_MMXq_MEMq) = PMADDWD<V64W, V64, MV64>;

namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(PMADDUBSW, D dst, S1 src1, S2 src2) {
  auto lhs_vec = UReadV8(src1);
  auto rhs_vec = SReadV8(src2);
  auto dst_vec = SClearV16(SReadV16(dst));

  // Multiply and Add Packed Signed and Unsigned Bytes
  auto vec_count = NumVectorElems(lhs_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i += 2) {
    auto mul1 = SMul(Int16(UExtractV8(lhs_vec, i)),
                     Int16(SExtractV8(rhs_vec, i)));
    auto mul2 = SMul(Int16(UExtractV8(lhs_vec, i+1)),
                     Int16(SExtractV8(rhs_vec, i+1)));
    auto add_elem = SAdd(mul2, mul1);
    auto or_elem = SOr(mul2, mul1);
    auto and_elem = SAnd(mul2, mul1);
    auto tmp = Select(
        SCmpLt(SAnd(add_elem, SNot(or_elem)), decltype(add_elem)(0)),
        decltype(add_elem)(0x7FFF),
        add_elem);
    auto value = Select(
        SCmpLt(SAnd(SNot(add_elem), and_elem), decltype(add_elem)(0)),
        decltype(add_elem)(0x8000),
        tmp);
    dst_vec = SInsertV16(dst_vec, i/2, value);
  }
  SWriteV16(dst, dst_vec);
}

}  // namespace

DEF_ISEL(PMADDUBSW_MMXq_MMXq) = PMADDUBSW<V64W, V64, V64>;
DEF_ISEL(PMADDUBSW_MMXq_MEMq) = PMADDUBSW<V64W, V64, MV64>;

namespace {

template <typename D, typename S1>
DEF_SEM(PABSB, D dst, S1 src1) {
  auto src_vec = SReadV8(src1);
  auto dst_vec = SClearV8(SReadV8(dst));
  auto vec_count = NumVectorElems(src_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto src_entry = SExtractV8(src_vec, i);
    auto mask = SShr(src_entry, decltype(src_entry)(7));
    auto abs_value = SSub(SXor(src_entry, mask), mask);
    dst_vec = SInsertV8(dst_vec, i, abs_value);
  }
  SWriteV8(dst, dst_vec);
}

template <typename D, typename S1>
DEF_SEM(PABSW, D dst, S1 src1) {
  auto src_vec = SReadV16(src1);
  auto dst_vec = SClearV16(SReadV16(dst));
  auto vec_count = NumVectorElems(src_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto src_entry = SExtractV16(src_vec, i);
    auto mask = SShr(src_entry, decltype(src_entry)(15));
    auto abs_value = SSub(SXor(src_entry, mask), mask);
    dst_vec = SInsertV16(dst_vec, i, abs_value);
  }
  SWriteV16(dst, dst_vec);
}

template <typename D, typename S1>
DEF_SEM(PABSD, D dst, S1 src1) {
  auto src_vec = SReadV32(src1);
  auto dst_vec = SClearV32(SReadV32(dst));
  auto vec_count = NumVectorElems(src_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto src_entry = SExtractV32(src_vec, i);
    auto mask = SShr(src_entry, decltype(src_entry)(31));
    auto abs_value = SSub(SXor(src_entry, mask), mask);
    dst_vec = SInsertV32(dst_vec, i, abs_value);
  }
  SWriteV32(dst, dst_vec);
}
}  // namespace

DEF_ISEL(PABSB_MMXq_MMXq) = PABSB<V64W, V64>;
DEF_ISEL(PABSB_MMXq_MEMq) = PABSB<V64W, MV64>;

DEF_ISEL(PABSW_MMXq_MMXq) = PABSW<V64W, V64>;
DEF_ISEL(PABSW_MMXq_MEMq) = PABSW<V64W, MV64>;

DEF_ISEL(PABSD_MMXq_MMXq) = PABSD<V64W, V64>;
DEF_ISEL(PABSD_MMXq_MEMq) = PABSD<V64W, MV64>;

namespace {
// Need a better solution for handling PACKSS;
// Soln : Sign extension and compare
template <typename D, typename S1, typename S2>
DEF_SEM(PACKSSWB, D dst, S1 src1, S2 src2) {
  auto src1_vec = SReadV16(src1);
  auto src2_vec = SReadV16(src2);
  auto dst_vec = SClearV8(SReadV8(dst));

  // Convert signed word to saturated signed byte
  auto vec_count = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = SExtractV16(src1_vec, i);
    auto v2 = SExtractV8(dst_vec, i);
    auto value = Select(SCmpGt(v1, SExt(Maximize(v2))),
                        Maximize(v2),
                        Trunc(v1));
    value = Select(SCmpLt(v1, SExt(Minimize(v2))), Minimize(v2), value);
    dst_vec = SInsertV8(dst_vec, i, value);
  }
  _Pragma("unroll")
  for (size_t i = 0; i < NumVectorElems(src2_vec); i++) {
    auto v1 = SExtractV16(src2_vec, i);
    auto v2 = SExtractV8(dst_vec, i);
    auto value = Select(SCmpGt(v1, SExt(Maximize(v2))),
                        Maximize(v2),
                        Trunc(v1));
    value = Select(SCmpLt(v1, SExt(Minimize(v2))), Minimize(v2), value);
    dst_vec = SInsertV8(dst_vec, i+vec_count, value);
  }
  SWriteV8(dst, dst_vec);
}
}  // namespace

DEF_ISEL(PACKSSWB_MMXq_MMXq) = PACKSSWB<V64W, V64, V64>;
DEF_ISEL(PACKSSWB_MMXq_MEMq) = PACKSSWB<V64W, V64, MV64>;

namespace {
template <typename D, typename S1, typename S2>
DEF_SEM(PACKSSDW, D dst, S1 src1, S2 src2) {
  auto src1_vec = SReadV32(src1);
  auto src2_vec = SReadV32(src2);
  auto dst_vec = SClearV16(SReadV16(dst));
  // Convert signed word to saturated signed byte
  auto vec_count = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = SExtractV32(src1_vec, i);
    auto v2 = SExtractV16(dst_vec, i);
    auto value = Select(SCmpGt(v1, SExt(Maximize(v2))),
                        Maximize(v2),
                        Trunc(v1));
    value = Select(SCmpLt(v1, SExt(Minimize(v2))), Minimize(v2), value);
    dst_vec = SInsertV16(dst_vec, i, value);
  }
  _Pragma("unroll")
  for (size_t i = 0; i < NumVectorElems(src2_vec); i++) {
    auto v1 = SExtractV32(src2_vec, i);
    auto v2 = SExtractV16(dst_vec, i);
    auto value = Select(SCmpGt(v1, SExt(Maximize(v2))),
                        Maximize(v2),
                        Trunc(v1));
    value = Select(SCmpLt(v1, SExt(Minimize(v2))), Minimize(v2), value);
    dst_vec = SInsertV16(dst_vec, i+vec_count, value);
  }
  SWriteV16(dst, dst_vec);
}
}  // namespace

DEF_ISEL(PACKSSDW_MMXq_MMXq) = PACKSSDW<V64W, V64, V64>;
DEF_ISEL(PACKSSDW_MMXq_MEMq) = PACKSSDW<V64W, V64, MV64>;

namespace {
template <typename D, typename S1, typename S2>
DEF_SEM(PEXTRW, D dst, S1 src1, S2 src2) {
  auto src1_vec = UReadV16(src1);
  auto count = Read(src2);
  auto sel_index = UAnd(count, UInt8(0x3));
  auto word = UExtractV16(src1_vec, sel_index);
  WriteZExt(dst, word);
}
}  // namespace

DEF_ISEL(PEXTRW_GPR32_MMXq_IMMb) = PEXTRW<R32W, V64, I8>;

namespace {
template <typename D, typename S1, typename S2, typename S3>
DEF_SEM(PALIGNR_64, D dst, S1 src1, S2 src2, S3 imm1) {
  auto src1_vec = UReadV64(src1);
  auto src2_vec = UReadV64(src2);
  auto shift = UMul(Read(imm1), 0x8);
  auto dst_vec = UClearV64(UReadV64(dst));

  // Concat src and dst and right shift the bits
  auto src1_elem = UExtractV64(src1_vec, 0);
  auto src2_elem = UExtractV64(src2_vec, 0);
  auto temp = UOr(UShl(src1_elem, decltype(src1_elem)(64-shift)),
                  UShr(src2_elem, decltype(src2_elem)(shift)));
  dst_vec = UInsertV64(dst_vec, 0, temp);
  UWriteV64(dst, dst_vec);
}
}  // namespace

DEF_ISEL(PALIGNR_MMXq_MMXq_IMMb) = PALIGNR_64<V64W, V64, V64, I8>;
DEF_ISEL(PALIGNR_MMXq_MEMq_IMMb) = PALIGNR_64<V64W, V64, MV64, I8>;

namespace {
template <typename D, typename S1, typename S2>
DEF_SEM(PCMPEQB, D dst, S1 src1, S2 src2) {
  auto lhs_vec = UReadV8(src1);
  auto rhs_vec = UReadV8(src2);
  auto dst_vec = UClearV8(UReadV8(dst));

  //     Compare packed data for equal
  auto vec_count = NumVectorElems(lhs_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = UExtractV8(lhs_vec, i);
    auto v2 = UExtractV8(rhs_vec, i);
    auto temp = Select(UCmpEq(v1, v2), Maximize(v1), Minimize(v1));
    dst_vec = UInsertV8(dst_vec, i, temp);
  }
  UWriteV8(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PCMPEQW, D dst, S1 src1, S2 src2) {
  auto lhs_vec = UReadV16(src1);
  auto rhs_vec = UReadV16(src2);
  auto dst_vec = UClearV16(UReadV16(dst));

  //     Compare packed data for equal
  auto vec_count = NumVectorElems(lhs_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = UExtractV16(lhs_vec, i);
    auto v2 = UExtractV16(rhs_vec, i);
    auto temp = Select(UCmpEq(v1, v2), Maximize(v1), Minimize(v1));
    dst_vec = UInsertV16(dst_vec, i, temp);
  }
  UWriteV16(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PCMPEQD, D dst, S1 src1, S2 src2) {
  auto lhs_vec = UReadV32(src1);
  auto rhs_vec = UReadV32(src2);
  auto dst_vec = UClearV32(UReadV32(dst));

  //     Compare packed data for equal
  auto vec_count = NumVectorElems(lhs_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = UExtractV32(lhs_vec, i);
    auto v2 = UExtractV32(rhs_vec, i);
    auto temp = Select(UCmpEq(v1, v2), Maximize(v1), Minimize(v1));
    dst_vec = UInsertV32(dst_vec, i, temp);
  }
  UWriteV32(dst, dst_vec);
}

}  // namespace

DEF_ISEL(PCMPEQB_MMXq_MMXq) = PCMPEQB<V64W, V64, V64>;
DEF_ISEL(PCMPEQB_MMXq_MEMq) = PCMPEQB<V64W, V64, MV64>;

DEF_ISEL(PCMPEQW_MMXq_MMXq) = PCMPEQW<V64W, V64, V64>;
DEF_ISEL(PCMPEQW_MMXq_MEMq) = PCMPEQW<V64W, V64, MV64>;

DEF_ISEL(PCMPEQD_MMXq_MMXq) = PCMPEQD<V64W, V64, V64>;
DEF_ISEL(PCMPEQD_MMXq_MEMq) = PCMPEQD<V64W, V64, MV64>;

namespace {
template <typename D, typename S1, typename S2>
DEF_SEM(PCMPGTB, D dst, S1 src1, S2 src2) {
  auto lhs_vec = SReadV8(src1);
  auto rhs_vec = SReadV8(src2);
  auto dst_vec = SClearV8(SReadV8(dst));

  //     Compare packed data for equal
  auto vec_count = NumVectorElems(lhs_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto temp = Select(
        SCmpGt(SExtractV8(lhs_vec, i), SExtractV8(rhs_vec, i)),
        Int8(0xFF),
        Int8(0x00));
    dst_vec = SInsertV8(dst_vec, i, temp);
  }
  SWriteV8(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PCMPGTW, D dst, S1 src1, S2 src2) {
  auto lhs_vec = SReadV16(src1);
  auto rhs_vec = SReadV16(src2);
  auto dst_vec = SClearV16(SReadV16(dst));

  //     Compare packed data for equal
  auto vec_count = NumVectorElems(lhs_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto temp = Select(
        SCmpGt(SExtractV16(lhs_vec, i), SExtractV16(rhs_vec, i)),
        Int16(0xFFFF),
        Int16(0x00));
    dst_vec = SInsertV16(dst_vec, i, temp);
  }
  SWriteV16(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PCMPGTD, D dst, S1 src1, S2 src2) {
  auto lhs_vec = SReadV32(src1);
  auto rhs_vec = SReadV32(src2);
  auto dst_vec = SClearV32(SReadV32(dst));

  //     Compare packed data for equal
  auto vec_count = NumVectorElems(lhs_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = SExtractV32(lhs_vec, i);
    auto v2 = SExtractV32(rhs_vec, i);
    auto temp = Select(SCmpGt(v1, v2), Int32(0xFFFFFFFF), Int32(0x00));
    dst_vec = SInsertV32(dst_vec, i, temp);
  }
  SWriteV32(dst, dst_vec);
}

}  // namespace

DEF_ISEL(PCMPGTB_MMXq_MMXq) = PCMPGTB<V64W, V64, V64>;
DEF_ISEL(PCMPGTB_MMXq_MEMq) = PCMPGTB<V64W, V64, MV64>;

DEF_ISEL(PCMPGTW_MMXq_MMXq) = PCMPGTW<V64W, V64, V64>;
DEF_ISEL(PCMPGTW_MMXq_MEMq) = PCMPGTW<V64W, V64, MV64>;

DEF_ISEL(PCMPGTD_MMXq_MMXq) = PCMPGTD<V64W, V64, V64>;
DEF_ISEL(PCMPGTD_MMXq_MEMq) = PCMPGTD<V64W, V64, MV64>;

namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(PSRLW, D dst, S1 src1, S2 src2) {
  auto src1_vec = UReadV16(src1);
  auto count = Read(src2);
  auto dst_vec = UClearV16(UReadV16(dst));

  auto vec_count = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = UExtractV16(src1_vec, i);
    auto temp = Select(
        UCmpGt(count, static_cast<decltype(count)>(15)),
        static_cast<decltype(v1)>(0),
        UShr(v1, static_cast<decltype(v1)>(count)));
    dst_vec = UInsertV16(dst_vec, i, temp);
  }
  UWriteV16(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PSRLD, D dst, S1 src1, S2 src2) {
  auto src1_vec = UReadV32(src1);
  auto count = Read(src2);
  auto dst_vec = UClearV32(UReadV32(dst));

  auto vec_count = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = UExtractV32(src1_vec, i);
    auto temp = Select(
        UCmpGt(count, static_cast<decltype(count)>(31)),
        static_cast<decltype(v1)>(0),
        UShr(v1, static_cast<decltype(v1)>(count)));
    dst_vec = UInsertV32(dst_vec, i, temp);
  }
  UWriteV32(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PSRLQ, D dst, S1 src1, S2 src2) {
  auto src1_vec = UReadV64(src1);
  auto count = Read(src2);
  auto dst_vec = UClearV64(UReadV64(dst));

  auto vec_count = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = UExtractV64(src1_vec, i);
    auto temp = Select(
        UCmpGt(count, static_cast<decltype(count)>(63)),
        static_cast<decltype(v1)>(0),
        UShr(v1, static_cast<decltype(v1)>(count)));
    dst_vec = UInsertV64(dst_vec, i, temp);
  }
  UWriteV64(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PSRAW, D dst, S1 src1, S2 src2) {
  auto src1_vec = SReadV16(src1);
  auto count = Read(src2);
  auto dst_vec = SClearV16(SReadV16(dst));

  auto vec_count = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = SExtractV16(src1_vec, i);
    count = Select(
        UCmpGt(count, static_cast<decltype(count)>(15)),
        static_cast<decltype(count)>(16),
        count);
    dst_vec = SInsertV16(
        dst_vec, i, SShr(v1, static_cast<decltype(v1)>(count)));
  }
  SWriteV16(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PSRAD, D dst, S1 src1, S2 src2) {
  auto src1_vec = SReadV32(src1);
  auto count = Read(src2);
  auto dst_vec = SClearV32(SReadV32(dst));

  auto vec_count = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = SExtractV32(src1_vec, i);
    count = Select(
        UCmpGt(count, static_cast<decltype(count)>(31)),
        static_cast<decltype(count)>(32),
        count);
    dst_vec = SInsertV32(
        dst_vec, i, SShr(v1, static_cast<decltype(v1)>(count)));
  }
  SWriteV32(dst, dst_vec);
}

}  // namespace

DEF_ISEL(PSRLW_MMXq_IMMb) = PSRLW<V64W, V64, I8>;
DEF_ISEL(PSRLW_MMXq_MMXq) = PSRLW<V64W, V64, R64>;
DEF_ISEL(PSRLW_MMXq_MEMq) = PSRLW<V64W, V64, M64>;

DEF_ISEL(PSRLD_MMXq_IMMb) = PSRLD<V64W, V64, I8>;
DEF_ISEL(PSRLD_MMXq_MMXq) = PSRLD<V64W, V64, R64>;
DEF_ISEL(PSRLD_MMXq_MEMq) = PSRLD<V64W, V64, M64>;

DEF_ISEL(PSRLQ_MMXq_IMMb) = PSRLQ<V64W, V64, I8>;
DEF_ISEL(PSRLQ_MMXq_MMXq) = PSRLQ<V64W, V64, R64>;
DEF_ISEL(PSRLQ_MMXq_MEMq) = PSRLQ<V64W, V64, M64>;

DEF_ISEL(PSRAW_MMXq_IMMb) = PSRAW<V64W, V64, I8>;
DEF_ISEL(PSRAW_MMXq_MMXq) = PSRAW<V64W, V64, R64>;
DEF_ISEL(PSRAW_MMXq_MEMq) = PSRAW<V64W, V64, M64>;

DEF_ISEL(PSRAD_MMXq_IMMb) = PSRAD<V64W, V64, I8>;
DEF_ISEL(PSRAD_MMXq_MMXq) = PSRAD<V64W, V64, R64>;
DEF_ISEL(PSRAD_MMXq_MEMq) = PSRAD<V64W, V64, M64>;

namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(PSLLW, D dst, S1 src1, S2 src2) {
  auto src1_vec = SReadV16(src1);
  auto count = Read(src2);
  auto dst_vec = SClearV16(SReadV16(dst));

  auto vec_count = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = SExtractV16(src1_vec, i);
    auto temp = Select(
        UCmpGt(count, static_cast<decltype(count)>(15)),
        static_cast<decltype(v1)>(0),
        SShl(v1, static_cast<decltype(v1)>(count)));
    dst_vec = SInsertV16(dst_vec, i, temp);
  }
  SWriteV16(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PSLLD, D dst, S1 src1, S2 src2) {
  auto src1_vec = SReadV32(src1);
  auto count = Read(src2);
  auto dst_vec = SClearV32(SReadV32(dst));

  auto vec_count = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = SExtractV32(src1_vec, i);
    auto temp = Select(
        UCmpGt(count, static_cast<decltype(count)>(31)),
        static_cast<decltype(v1)>(0),
        SShl(v1, static_cast<decltype(v1)>(count)));
    dst_vec = SInsertV32(dst_vec, i, temp);
  }
  SWriteV32(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PSLLQ, D dst, S1 src1, S2 src2) {
  auto src1_vec = SReadV64(src1);
  auto count = Read(src2);
  auto dst_vec = SClearV64(SReadV64(dst));

  auto vec_count = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = SExtractV64(src1_vec, i);
    auto temp = Select(
        UCmpGt(count, static_cast<decltype(count)>(63)),
        static_cast<decltype(v1)>(0),
        SShl(v1, static_cast<decltype(v1)>(count)));
    dst_vec = SInsertV64(dst_vec, i, temp);
  }
  SWriteV64(dst, dst_vec);
}

}  // namespace

DEF_ISEL(PSLLW_MMXq_IMMb) = PSLLW<V64W, V64, I8>;
DEF_ISEL(PSLLW_MMXq_MMXq) = PSLLW<V64W, V64, R64>;
DEF_ISEL(PSLLW_MMXq_MEMq) = PSLLW<V64W, V64, M64>;

DEF_ISEL(PSLLD_MMXq_IMMb) = PSLLD<V64W, V64, I8>;
DEF_ISEL(PSLLD_MMXq_MMXq) = PSLLD<V64W, V64, R64>;
DEF_ISEL(PSLLD_MMXq_MEMq) = PSLLD<V64W, V64, M64>;

DEF_ISEL(PSLLQ_MMXq_IMMb) = PSLLQ<V64W, V64, I8>;
DEF_ISEL(PSLLQ_MMXq_MMXq) = PSLLQ<V64W, V64, R64>;
DEF_ISEL(PSLLQ_MMXq_MEMq) = PSLLQ<V64W, V64, M64>;

namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(PSIGNB, D dst, S1 src1, S2 src2) {
  auto src1_vec = SReadV8(src1);
  auto src2_vec = SReadV8(src1);
  auto dst_vec = SClearV8(SReadV8(dst));

  auto vec_count = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = SExtractV8(src1_vec, i);
    auto v2 = SExtractV8(src2_vec, i);
    auto value = Select(SCmpGte(v2, static_cast<decltype(v2)>(0)),
                        v1, SNeg(v1));
    value = Select(SCmpEq(v2, static_cast<decltype(v2)>(0)),
                   static_cast<decltype(value)>(0), value);
    dst_vec = SInsertV8(dst_vec, i, value);
  }
  SWriteV8(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PSIGNW, D dst, S1 src1, S2 src2) {
  auto src1_vec = SReadV16(src1);
  auto src2_vec = SReadV16(src1);
  auto dst_vec = SClearV16(SReadV16(dst));

  auto vec_count = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = SExtractV16(src1_vec, i);
    auto v2 = SExtractV16(src2_vec, i);
    auto value = Select(SCmpGte(v2, static_cast<decltype(v2)>(0)),
                        v1, SNeg(v1));
    value = Select(SCmpEq(v2, static_cast<decltype(v2)>(0)),
                   static_cast<decltype(value)>(0), value);
    dst_vec = SInsertV16(dst_vec, i, value);
  }
  SWriteV16(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PSIGND, D dst, S1 src1, S2 src2) {
  auto src1_vec = SReadV32(src1);
  auto src2_vec = SReadV32(src1);
  auto dst_vec = SClearV32(SReadV32(dst));

  auto vec_count = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = SExtractV32(src1_vec, i);
    auto v2 = SExtractV32(src2_vec, i);
    auto value = Select(SCmpGte(v2, static_cast<decltype(v2)>(0)),
                        v1, SNeg(v1));
    value = Select(SCmpEq(v2, static_cast<decltype(v2)>(0)),
                   static_cast<decltype(value)>(0), value);
    dst_vec = SInsertV32(dst_vec, i, value);
  }
  SWriteV32(dst, dst_vec);
}

}  // namespace

DEF_ISEL(PSIGNB_MMXq_MMXq) = PSIGNB<V64W, V64, V64>;
DEF_ISEL(PSIGNB_MMXq_MEMq) = PSIGNB<V64W, V64, MV64>;

DEF_ISEL(PSIGNW_MMXq_MMXq) = PSIGNW<V64W, V64, V64>;
DEF_ISEL(PSIGNW_MMXq_MEMq) = PSIGNW<V64W, V64, MV64>;

DEF_ISEL(PSIGND_MMXq_MMXq) = PSIGND<V64W, V64, V64>;
DEF_ISEL(PSIGND_MMXq_MEMq) = PSIGND<V64W, V64, MV64>;

namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(PSHUFB, D dst, S1 src1, S2 src2) {
  auto src1_vec = UReadV8(src1);
  auto src2_vec = UReadV8(src1);
  auto dst_vec = UClearV8(UReadV8(dst));

  auto vec_count = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    uint8_t v1 = UExtractV8(src2_vec, i);
    uint8_t index = UAnd(v1, uint8_t(0x7));
    uint8_t v2 = UExtractV8(src1_vec, index);
    uint8_t mask = UShr(v1, uint8_t(0x7));
    uint8_t value = Select(UCmpEq(mask, uint8_t(0)), v2, uint8_t(0));
    dst_vec = UInsertV8(dst_vec, i, value);
  }
  UWriteV8(dst, dst_vec);
}

template <typename D, typename S1>
DEF_SEM(PSHUFW, D dst, S1 src1, uint8_t order) {
  auto src_vec = UReadV16(src1);
  auto dst_vec = UClearV16(UReadV16(dst));

  auto vec_count = NumVectorElems(dst_vec);
  _Pragma("unroll")
  for (uint8_t i = 0; i < vec_count; i++) {
    auto mask = UAnd(UShr(order, i), uint8_t(0x3));
    auto v1 = UExtractV16(src_vec, mask);
    dst_vec = UInsertV16(dst_vec, i, v1);
  }
  UWriteV16(dst, dst_vec);
}

}  // namespace

DEF_ISEL(PSHUFB_MMXq_MMXq) = PSHUFB<V64W, V64, V64>;
DEF_ISEL(PSHUFB_MMXq_MEMq) = PSHUFB<V64W, V64, MV64>;

DEF_ISEL(PSHUFW_MMXq_MMXq) = PSHUFW<V64W, V64>;
DEF_ISEL(PSHUFW_MMXq_MEMq) = PSHUFW<V64W, MV64>;

namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(PSADBW, D dst, S1 src1, S2 src2) {
  auto src1_vec = UReadV8(src1);
  auto src2_vec = UReadV8(src2);
  auto dst_vec = UClearV16(UReadV16(dst));
  auto entry0 =  UExtractV16(dst_vec, 0);

  auto vec_count = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = UExtractV8(src1_vec, i);
    auto v2 = UExtractV8(src2_vec, i);
    auto value = Select(UCmpGte(v1, v2), USub(v1, v2), USub(v2, v1));
    entry0 += ZExt(value);
  }
  UWriteV16(dst, UInsertV16(dst_vec, 0, entry0));
}

}  // namespace

DEF_ISEL(PSADBW_MMXq_MMXq) = PSADBW<V64W, V64, V64>;
DEF_ISEL(PSADBW_MMXq_MEMq) = PSADBW<V64W, V64, MV64>;

namespace {
template <typename D, typename S1, typename S2>
DEF_SEM(PMULUDQ, D dst, S1 src1, S2 src2) {
  auto src1_vec = UReadV32(src1);
  auto src2_vec = UReadV32(src2);
  auto dst_vec = UClearV64(UReadV64(dst));
  auto v1 = ZExt(UExtractV32(src1_vec, 0));
  auto v2 = ZExt(UExtractV32(src2_vec, 0));
  auto mul = UMul(v1, v2);
  UWriteV64(dst, UInsertV64(dst_vec, 0, mul));
}

template <typename D, typename S1, typename S2>
DEF_SEM(PMULLW, D dst, S1 src1, S2 src2) {
  auto src1_vec = SReadV16(src1);
  auto src2_vec = SReadV16(src2);
  auto dst_vec = SClearV16(SReadV16(dst));

  auto vec_count = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = SExtractV16(src1_vec, i);
    auto v2 = SExtractV16(src2_vec, i);
    auto mul = SMul(SExt(v1), SExt(v2));
    dst_vec = SInsertV16(dst_vec, i, Trunc(mul));
  }
  SWriteV16(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PMULHW, D dst, S1 src1, S2 src2) {
  auto src1_vec = SReadV16(src1);
  auto src2_vec = SReadV16(src2);
  auto dst_vec = SClearV16(SReadV16(dst));

  auto vec_count = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = SExtractV16(src1_vec, i);
    auto v2 = SExtractV16(src2_vec, i);
    auto mul = SMul(SExt(v1), SExt(v2));
    dst_vec = SInsertV16(dst_vec, i, Trunc(SShr(mul, decltype(mul)(16))));
  }
  SWriteV16(dst, dst_vec);
}

template <typename D, typename S1, typename S2>
DEF_SEM(PMULHUW, D dst, S1 src1, S2 src2) {
  auto src1_vec = UReadV16(src1);
  auto src2_vec = UReadV16(src2);
  auto dst_vec = UClearV16(UReadV16(dst));

  auto vec_count = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = UExtractV16(src1_vec, i);
    auto v2 = UExtractV16(src2_vec, i);
    auto mul = UMul(ZExt(v1), ZExt(v2));
    dst_vec = UInsertV16(dst_vec, i, Trunc(UShr(mul, decltype(mul)(16))));
  }
  UWriteV16(dst, dst_vec);
}


}  // namespace

DEF_ISEL(PMULUDQ_MMXq_MMXq) = PMULUDQ<V64W, V64, V64>;
DEF_ISEL(PMULUDQ_MMXq_MEMq) = PMULUDQ<V64W, V64, MV64>;

DEF_ISEL(PMULLW_MMXq_MMXq) = PMULLW<V64W, V64, V64>;
DEF_ISEL(PMULLW_MMXq_MEMq) = PMULLW<V64W, V64, MV64>;

DEF_ISEL(PMULHW_MMXq_MMXq) = PMULHW<V64W, V64, V64>;
DEF_ISEL(PMULHW_MMXq_MEMq) = PMULHW<V64W, V64, MV64>;

DEF_ISEL(PMULHUW_MMXq_MMXq) = PMULHUW<V64W, V64, V64>;
DEF_ISEL(PMULHUW_MMXq_MEMq) = PMULHUW<V64W, V64, MV64>;

namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(PMOVMSKB, D dst, S1 src1, S2 src2) {
  auto src_vec = UReadV8(src2);
  auto r32 = Read(src1);
  // reset all bits to zero
  r32 = static_cast<decltype(r32)>(0x0);
  auto vec_count = NumVectorElems(src_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = UExtractV8(src_vec, i);
    auto mask_bit = UAnd(
        UShr(v1, decltype(v1)(vec_count-1-i)),
        UShl(decltype(v1)(0x1), decltype(v1)(i)));
    r32 = UOr(r32, decltype(r32)(mask_bit));
  }
  WriteZExt(dst, r32);
}

}  // namespace

DEF_ISEL(PMOVMSKB_GPR32_MMXq) = PMOVMSKB<R32W, R32, V64>;

namespace {

template <typename D, typename S1, typename S2>
DEF_SEM(PINSRW, D dst, S1 src1, S2 src2) {
  auto dst_vec = UClearV16(UReadV16(dst));
  auto value = Read(src1);
  auto index = Read(src2);
  UWriteV16(dst, UInsertV16(dst_vec, index, UInt16(value)));
}

}  // namespace

DEF_ISEL(PINSRW_MMXq_MEMw_IMMb) = PINSRW<V64W, M16, I8>;
DEF_ISEL(PINSRW_MMXq_GPR32_IMMb) = PINSRW<V64W, R32, I8>;

DEF_ISEL_SEM(MOVNTQ_MEMq_MMXq, M64W dst, R64 src1) {
  Write(dst, Read(src1));
}

namespace {
template <typename S1, typename S2>
DEF_SEM(MASKMOVQ, S1 src1, S2 src2) {
  auto src1_vec = UReadV8(src1);
  auto src2_vec = UReadV8(src2);
  auto xdi = Read(REG_XDI);

  auto vec_count = NumVectorElems(src1_vec);
  _Pragma("unroll")
  for (size_t i = 0; i < vec_count; i++) {
    auto v1 = UExtractV8(src1_vec, i);
    auto v2 = UExtractV8(src2_vec, i);
    auto dst_addr = UAdd(xdi, decltype(xdi)(sizeof(v1)*i));
    if (UCmpEq(UShl(v2, decltype(v2)(0x7)), decltype(v2)(0x1))) {
      Write(WritePtr<decltype(v1)>(dst_addr _IF_32BIT(REG_DS)), v1);
    }
  }
}

}  // namespace

DEF_ISEL(MASKMOVQ_MMXq_MMXq) = MASKMOVQ<V64, V64>;


DEF_ISEL_SEM(EMMS) {
  state.mmx.elems[0].val.qwords.elems[0] = __remill_undefined_64();
  state.mmx.elems[1].val.qwords.elems[0] = __remill_undefined_64();
  state.mmx.elems[2].val.qwords.elems[0] = __remill_undefined_64();
  state.mmx.elems[3].val.qwords.elems[0] = __remill_undefined_64();
  state.mmx.elems[4].val.qwords.elems[0] = __remill_undefined_64();
  state.mmx.elems[5].val.qwords.elems[0] = __remill_undefined_64();
  state.mmx.elems[6].val.qwords.elems[0] = __remill_undefined_64();
  state.mmx.elems[7].val.qwords.elems[0] = __remill_undefined_64();

  state.st.elems[0].val = __remill_undefined_f64();
  state.st.elems[1].val = __remill_undefined_f64();
  state.st.elems[2].val = __remill_undefined_f64();
  state.st.elems[3].val = __remill_undefined_f64();
  state.st.elems[4].val = __remill_undefined_f64();
  state.st.elems[5].val = __remill_undefined_f64();
  state.st.elems[6].val = __remill_undefined_f64();
  state.st.elems[7].val = __remill_undefined_f64();

  // TODO(pag): Add FPU tag word stuff to the `State` structure, and reset
  //            it here.
}

DEF_ISEL(FEMMS) = EMMS;

// 565:117 PHSUBD PHSUBD_MMXq_MEMq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 569:118 PHSUBD PHSUBD_MMXq_MMXq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 639:135 PMULHRSW PMULHRSW_MMXq_MEMq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 643:136 PMULHRSW PMULHRSW_MMXq_MMXq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 671:143 PHSUBW PHSUBW_MMXq_MEMq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 675:144 PHSUBW PHSUBW_MMXq_MMXq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 918:197 PCMPGTW PCMPGTW_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 922:198 PCMPGTW PCMPGTW_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 952:205 PCMPGTB PCMPGTB_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 956:206 PCMPGTB PCMPGTB_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 968:209 PCMPGTD PCMPGTD_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 972:210 PCMPGTD PCMPGTD_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 1077:235 PACKUSWB PACKUSWB_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: HALF_WIDE_OUTPUT NOTSX
// 1081:236 PACKUSWB PACKUSWB_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: HALF_WIDE_OUTPUT NOTSX
// 1385:308 PSIGNW PSIGNW_MMXq_MEMq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 1389:309 PSIGNW PSIGNW_MMXq_MMXq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 1459:325 PSIGND PSIGND_MMXq_MEMq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 1463:326 PSIGND PSIGND_MMXq_MMXq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 1483:331 PSIGNB PSIGNB_MMXq_MEMq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 1487:332 PSIGNB PSIGNB_MMXq_MMXq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 1584:353 PSUBD PSUBD_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 1588:354 PSUBD PSUBD_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 1760:388 PHADDSW PHADDSW_MMXq_MEMq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 1764:389 PHADDSW PHADDSW_MMXq_MMXq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 1925:425 PSADBW PSADBW_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 1929:426 PSADBW PSADBW_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 2197:482 PADDUSW PADDUSW_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 2201:483 PADDUSW PADDUSW_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 2239:490 PMADDUBSW PMADDUBSW_MMXq_MEMq MMX SSSE3 SSSE3 ATTRIBUTES: DOUBLE_WIDE_OUTPUT NOTSX
// 2243:491 PMADDUBSW PMADDUBSW_MMXq_MMXq MMX SSSE3 SSSE3 ATTRIBUTES: DOUBLE_WIDE_OUTPUT NOTSX
// 2283:498 PADDUSB PADDUSB_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 2287:499 PADDUSB PADDUSB_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 2437:533 PACKSSDW PACKSSDW_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: HALF_WIDE_OUTPUT NOTSX
// 2441:534 PACKSSDW PACKSSDW_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: HALF_WIDE_OUTPUT NOTSX
// 2460:539 PMULLW PMULLW_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 2464:540 PMULLW PMULLW_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 2498:549 PHSUBSW PHSUBSW_MMXq_MEMq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 2502:550 PHSUBSW PHSUBSW_MMXq_MMXq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 2546:559 PCMPEQW PCMPEQW_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 2550:560 PCMPEQW PCMPEQW_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 2600:570 PCMPEQB PCMPEQB_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 2604:571 PCMPEQB PCMPEQB_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 2616:574 PCMPEQD PCMPEQD_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 2620:575 PCMPEQD PCMPEQD_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 2691:591 PUNPCKLWD PUNPCKLWD_MMXq_MEMd MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 2695:592 PUNPCKLWD PUNPCKLWD_MMXq_MMXd MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 2760:605 PADDSW PADDSW_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 2764:606 PADDSW PADDSW_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 2807:616 PXOR PXOR_MMXq_MEMq LOGICAL MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 2811:617 PXOR PXOR_MMXq_MMXq LOGICAL MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 3203:700 PSUBB PSUBB_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 3207:701 PSUBB PSUBB_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 3267:714 PSUBUSW PSUBUSW_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 3271:715 PSUBUSW PSUBUSW_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 3288:719 PSUBW PSUBW_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 3292:720 PSUBW PSUBW_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 3460:753 PADDW PADDW_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 3464:754 PADDW PADDW_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 3476:757 PMAXSW PMAXSW_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 3480:758 PMAXSW PMAXSW_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 3620:787 PADDD PADDD_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 3624:788 PADDD PADDD_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 3644:793 PADDB PADDB_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 3648:794 PADDB PADDB_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 3766:820 PADDQ PADDQ_MMXq_MEMq MMX SSE2 SSE2 ATTRIBUTES: NOTSX
// 3770:821 PADDQ PADDQ_MMXq_MMXq MMX SSE2 SSE2 ATTRIBUTES: NOTSX
// 3858:842 PABSW PABSW_MMXq_MEMq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 3862:843 PABSW PABSW_MMXq_MMXq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 4019:876 PMULHUW PMULHUW_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 4023:877 PMULHUW PMULHUW_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 4095:895 PHADDD PHADDD_MMXq_MEMq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 4099:896 PHADDD PHADDD_MMXq_MMXq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 4111:899 POR POR_MMXq_MEMq LOGICAL MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 4115:900 POR POR_MMXq_MMXq LOGICAL MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 4385:950 PSLLD PSLLD_MMXq_IMMb MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 4393:952 PSLLD PSLLD_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 4397:953 PSLLD PSLLD_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 4518:980 PSLLW PSLLW_MMXq_IMMb MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 4526:982 PSLLW PSLLW_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 4530:983 PSLLW PSLLW_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 4558:990 PSLLQ PSLLQ_MMXq_IMMb MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 4566:992 PSLLQ PSLLQ_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 4570:993 PSLLQ PSLLQ_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 4684:1017 PSUBUSB PSUBUSB_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 4688:1018 PSUBUSB PSUBUSB_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 4784:1038 PMOVMSKB PMOVMSKB_GPR32_MMXq MMX MMX SSE ATTRIBUTES: NOTSX
// 4923:1060 PUNPCKLDQ PUNPCKLDQ_MMXq_MEMd MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 4927:1061 PUNPCKLDQ PUNPCKLDQ_MMXq_MMXd MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 5054:1088 PANDN PANDN_MMXq_MEMq LOGICAL MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 5058:1089 PANDN PANDN_MMXq_MMXq LOGICAL MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 5203:1120 PALIGNR PALIGNR_MMXq_MEMq_IMMb MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 5208:1121 PALIGNR PALIGNR_MMXq_MMXq_IMMb MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 5258:1131 PMULHW PMULHW_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 5262:1132 PMULHW PMULHW_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 5374:1157 MOVQ MOVQ_MMXq_MEMq_0F6E DATAXFER MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 5378:1158 MOVQ MOVQ_MMXq_GPR64 DATAXFER MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 5382:1159 MOVQ MOVQ_MEMq_MMXq_0F7E DATAXFER MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 5386:1160 MOVQ MOVQ_GPR64_MMXq DATAXFER MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 5390:1161 MOVQ MOVQ_MMXq_MEMq_0F6F DATAXFER MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 5394:1162 MOVQ MOVQ_MMXq_MMXq_0F6F DATAXFER MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 5398:1163 MOVQ MOVQ_MEMq_MMXq_0F7F DATAXFER MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 5402:1164 MOVQ MOVQ_MMXq_MMXq_0F7F DATAXFER MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 5406:1165 PMINSW PMINSW_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 5410:1166 PMINSW PMINSW_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 5552:1196 PSHUFB PSHUFB_MMXq_MEMq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 5556:1197 PSHUFB PSHUFB_MMXq_MMXq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 5708:1234 PSHUFW PSHUFW_MMXq_MEMq_IMMb MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 5713:1235 PSHUFW PSHUFW_MMXq_MMXq_IMMb MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 5960:1291 PSRLQ PSRLQ_MMXq_IMMb MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 5968:1293 PSRLQ PSRLQ_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 5972:1294 PSRLQ PSRLQ_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 5984:1297 PSRLW PSRLW_MMXq_IMMb MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 5992:1299 PSRLW PSRLW_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 5996:1300 PSRLW PSRLW_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 6038:1310 PSRLD PSRLD_MMXq_IMMb MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 6046:1312 PSRLD PSRLD_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 6050:1313 PSRLD PSRLD_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 6385:1378 FEMMS FEMMS MMX 3DNOW 3DNOW ATTRIBUTES: X87_MMX_STATE_W
// 6393:1380 PADDSB PADDSB_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 6397:1381 PADDSB PADDSB_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 6723:1447 MOVD MOVD_MMXq_MEMd DATAXFER MMX PENTIUMMMX ATTRIBUTES: NOTSX UNALIGNED
// 6727:1448 MOVD MOVD_MMXq_GPR32 DATAXFER MMX PENTIUMMMX ATTRIBUTES: NOTSX UNALIGNED
// 6731:1449 MOVD MOVD_MMXq_MEMd DATAXFER MMX PENTIUMMMX ATTRIBUTES: NOTSX UNALIGNED
// 6735:1450 MOVD MOVD_MMXq_GPR32 DATAXFER MMX PENTIUMMMX ATTRIBUTES: NOTSX UNALIGNED
// 6739:1451 MOVD MOVD_MEMd_MMXd DATAXFER MMX PENTIUMMMX ATTRIBUTES: NOTSX UNALIGNED
// 6743:1452 MOVD MOVD_GPR32_MMXd DATAXFER MMX PENTIUMMMX ATTRIBUTES: NOTSX UNALIGNED
// 6747:1453 MOVD MOVD_MEMd_MMXd DATAXFER MMX PENTIUMMMX ATTRIBUTES: NOTSX UNALIGNED
// 6751:1454 MOVD MOVD_GPR32_MMXd DATAXFER MMX PENTIUMMMX ATTRIBUTES: NOTSX UNALIGNED
// 6907:1485 PABSD PABSD_MMXq_MEMq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX SIMD_SCALAR
// 6911:1486 PABSD PABSD_MMXq_MMXq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX SIMD_SCALAR
// 6930:1491 PABSB PABSB_MMXq_MEMq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 6934:1492 PABSB PABSB_MMXq_MMXq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 6956:1497 PSUBQ PSUBQ_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 6960:1498 PSUBQ PSUBQ_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 7020:1511 EMMS EMMS MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX X87_MMX_STATE_W

// 7126:1536 PHADDW PHADDW_MMXq_MEMq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 7130:1537 PHADDW PHADDW_MMXq_MMXq MMX SSSE3 SSSE3 ATTRIBUTES: NOTSX
// 7448:1602 PMULUDQ PMULUDQ_MMXq_MEMq MMX SSE2 SSE2 ATTRIBUTES: NOTSX
// 7452:1603 PMULUDQ PMULUDQ_MMXq_MMXq MMX SSE2 SSE2 ATTRIBUTES: NOTSX
// 7479:1609 PMADDWD PMADDWD_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: DOUBLE_WIDE_OUTPUT NOTSX
// 7483:1610 PMADDWD PMADDWD_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: DOUBLE_WIDE_OUTPUT NOTSX
// 7527:1619 PEXTRW PEXTRW_GPR32_MMXq_IMMb MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 7605:1635 PAND PAND_MMXq_MEMq LOGICAL MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 7609:1636 PAND PAND_MMXq_MMXq LOGICAL MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 7669:1650 PMAXUB PMAXUB_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 7673:1651 PMAXUB PMAXUB_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX

//DEF_ISEL(PUNPCKHWD_MMXq_MEMq) = PUNPCKHBW<V64W, V64, MV64>;
//DEF_ISEL(PUNPCKHWD_MMXq_MMXd) = PUNPCKHBW<V64W, V64, V32>;

// 8028:1731 PMINUB PMINUB_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 8032:1732 PMINUB PMINUB_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 8050:1736 PINSRW PINSRW_MMXq_MEMw_IMMb MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX UNALIGNED
// 8055:1737 PINSRW PINSRW_MMXq_GPR32_IMMb MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX UNALIGNED
// 8162:1758 PSUBSW PSUBSW_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 8166:1759 PSUBSW PSUBSW_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 8194:1766 PAVGW PAVGW_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 8198:1767 PAVGW PAVGW_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 8404:1809 PSUBSB PSUBSB_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 8408:1810 PSUBSB PSUBSB_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 8474:1823 PAVGB PAVGB_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 8478:1824 PAVGB PAVGB_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 8498:1829 MASKMOVQ MASKMOVQ_MMXq_MMXq DATAXFER MMX PENTIUMMMX ATTRIBUTES: FIXED_BASE0 MASKOP NOTSX
// 8545:1840 PSRAW PSRAW_MMXq_IMMb MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 8553:1842 PSRAW PSRAW_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 8557:1843 PSRAW PSRAW_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 8587:1850 PSRAD PSRAD_MMXq_IMMb MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 8595:1852 PSRAD PSRAD_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 8599:1853 PSRAD PSRAD_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 8611:1856 PACKSSWB PACKSSWB_MMXq_MEMq MMX MMX PENTIUMMMX ATTRIBUTES: HALF_WIDE_OUTPUT NOTSX
// 8615:1857 PACKSSWB PACKSSWB_MMXq_MMXq MMX MMX PENTIUMMMX ATTRIBUTES: HALF_WIDE_OUTPUT NOTSX
// 8730:1883 PUNPCKLBW PUNPCKLBW_MMXq_MEMd MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX
// 8734:1884 PUNPCKLBW PUNPCKLBW_MMXq_MMXd MMX MMX PENTIUMMMX ATTRIBUTES: NOTSX

#endif // REMILL_ARCH_X86_SEMANTICS_MMX_H_
