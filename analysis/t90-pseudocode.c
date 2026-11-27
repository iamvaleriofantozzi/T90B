/* Ghidra pseudocode, generated from t90.atk. Not buildable C. */

/* 08005150 thunk_FUN_080115f4 */

void thunk_FUN_080115f4(void)

{
  (*DAT_08005154)();
  return;
}


/* 0800515c FUN_0800515c */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0800515c(uint param_1)

{
  uint *puVar1;
  
  puVar1 = DAT_080051a4;
  if (param_1 < 0x1f41) {
    *DAT_080051a4 = 0;
  }
  else {
    *DAT_080051a4 = *DAT_080051a4 + 1;
    if ((3 < *puVar1) && ((*(byte *)(_DAT_080051a8 + 0x1c) & 0x10) == 0)) {
      FUN_0800f808(4,s_ctrl_task_080051e4,s____src_app_src_ctrl_task_c_080051c8,DAT_080051c4,0x44e,
                   s_short_circ__isen_MA__d_080051ab + 1,param_1);
    }
  }
  return;
}


/* 080051f0 FUN_080051f0 */

void FUN_080051f0(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = FUN_080094b4(2,DAT_080052b8);
  if (iVar3 != 0) {
    FUN_08005ff0(2,DAT_080052b8);
    piVar1 = DAT_080052c0;
    uVar4 = 0;
    for (iVar3 = 0; iVar3 < 0x14; iVar3 = iVar3 + 1) {
      uVar4 = uVar4 + *(ushort *)(DAT_080052bc + iVar3 * 6 + 4);
    }
    uVar4 = (uVar4 / 0x14) * 0xc91 >> 0xc;
    *DAT_080052c0 = *DAT_080052c0 + uVar4;
    piVar1[1] = piVar1[1] + 1;
    piVar2 = DAT_080052c0;
    if (0x200 < (uint)piVar1[1]) {
      DAT_080052c0[2] = (uint)(*piVar1 * 0x65) / 0x28 >> 9;
      *piVar2 = 0;
      piVar2[1] = 0;
    }
    piVar1 = DAT_080052c4;
    *DAT_080052c4 = *DAT_080052c4 + uVar4;
    piVar1[1] = piVar1[1] + 1;
    piVar1 = DAT_080052c8;
    *DAT_080052c8 = *DAT_080052c8 + uVar4;
    piVar1[1] = piVar1[1] + 1;
    piVar2 = DAT_080052c8;
    if (3 < (uint)piVar1[1]) {
      DAT_080052c8[2] = (uint)(*piVar1 * 0x65) / 0x78;
      *piVar2 = 0;
      piVar2[1] = 0;
      FUN_0800515c(piVar2[2]);
    }
  }
  return;
}


/* 080052cc Reset_Handler */

void Reset_Handler(void)

{
  (*DAT_080052e8)();
                    /* WARNING: Could not recover jumptable at 0x080052d2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_080052ec)();
  return;
}


/* 080052e2 FUN_080052e2 */

void FUN_080052e2(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}


/* 080052e6 FUN_080052e6 */

void FUN_080052e6(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}


/* 080052f0 FUN_080052f0 */

undefined8 FUN_080052f0(int param_1,int param_2,int param_3,int param_4)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  undefined8 uVar4;
  
  bVar1 = param_2 < 0;
  if (bVar1) {
    bVar2 = param_1 != 0;
    param_1 = -param_1;
    param_2 = -(uint)bVar2 - param_2;
  }
  bVar2 = param_4 < 0;
  if (bVar2) {
    bVar3 = param_3 != 0;
    param_3 = -param_3;
    param_4 = -(uint)bVar3 - param_4;
  }
  uVar4 = FUN_08005940(param_1,param_2,param_3,param_4);
  if (bVar1 != bVar2) {
    uVar4 = CONCAT44(-(uint)((int)uVar4 != 0) - (int)((ulonglong)uVar4 >> 0x20),-(int)uVar4);
  }
  return uVar4;
}


/* 08005352 FUN_08005352 */

void FUN_08005352(int param_1,uint param_2,int param_3,code *param_4)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  int iVar6;
  int local_28 [3];
  
  if ((1 < param_2) && (param_3 != 0)) {
    local_28[2] = 0;
    iVar2 = param_2 - 1;
    iVar6 = -1;
    local_28[1] = param_3;
    while( true ) {
      if (iVar2 <= local_28[2]) break;
      iVar3 = (*param_4)(local_28[2] * param_3 + param_1,iVar2 * param_3 + param_1);
      if (iVar3 < 1) {
        local_28[iVar6 + 1] = local_28[iVar6 + 1] + iVar6;
      }
      else {
        puVar4 = (undefined1 *)(iVar2 * param_3 + param_1);
        puVar5 = (undefined1 *)(local_28[2] * param_3 + param_1);
        for (iVar3 = param_3; iVar3 != 0; iVar3 = iVar3 + -1) {
          uVar1 = *puVar5;
          *puVar5 = *puVar4;
          *puVar4 = uVar1;
          puVar4 = puVar4 + 1;
          puVar5 = puVar5 + 1;
        }
        iVar6 = -iVar6;
      }
    }
    FUN_08005352(param_1,local_28[2],param_3,param_4);
    FUN_08005352(param_2 * param_3 + param_1,(param_2 - iVar2) + -1,param_3,param_4);
  }
  return;
}


/* 080053ee FUN_080053ee */

void FUN_080053ee(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  undefined4 uVar1;
  bool bVar2;
  
  if ((((uint)param_1 | (uint)param_2) & 3) == 0) {
    for (; 3 < param_3; param_3 = param_3 - 4) {
      uVar1 = *param_2;
      param_2 = param_2 + 1;
      *param_1 = uVar1;
      param_1 = param_1 + 1;
    }
  }
  while (bVar2 = param_3 != 0, param_3 = param_3 - 1, bVar2) {
    *(undefined1 *)param_1 = *(undefined1 *)param_2;
    param_1 = (undefined4 *)((int)param_1 + 1);
    param_2 = (undefined4 *)((int)param_2 + 1);
  }
  return;
}


/* 08005412 FUN_08005412 */

void FUN_08005412(undefined1 *param_1,int param_2,undefined1 param_3)

{
  bool bVar1;
  
  while (bVar1 = param_2 != 0, param_2 = param_2 + -1, bVar1) {
    *param_1 = param_3;
    param_1 = param_1 + 1;
  }
  return;
}


/* 08005420 FUN_08005420 */

void FUN_08005420(undefined4 param_1,undefined4 param_2)

{
  FUN_08005412(param_1,param_2,0);
  return;
}


/* 08005424 FUN_08005424 */

undefined4 FUN_08005424(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_08005412(param_1,param_3,param_2);
  return param_1;
}


/* 08005436 FUN_08005436 */

void FUN_08005436(int param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = (char *)(param_1 + -1);
  do {
    pcVar2 = pcVar2 + 1;
  } while (*pcVar2 != '\0');
  do {
    cVar1 = *param_2;
    *pcVar2 = cVar1;
    param_2 = param_2 + 1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  return;
}


/* 0800544e FUN_0800544e */

byte * FUN_0800544e(byte *param_1,byte *param_2)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  pbVar3 = param_2;
  pbVar4 = param_1;
LAB_08005456:
  pbVar2 = (byte *)(uint)*param_1;
  bVar1 = *pbVar3;
  if (pbVar2 != (byte *)0x0) goto code_r0x08005460;
  goto LAB_08005464;
code_r0x08005460:
  param_1 = param_1 + 1;
  pbVar3 = pbVar3 + 1;
  if (pbVar2 != (byte *)(uint)bVar1) {
LAB_08005464:
    pbVar3 = pbVar4;
    if (((byte *)(uint)bVar1 == (byte *)0x0) || (pbVar3 = pbVar2, pbVar2 == (byte *)0x0)) {
      return pbVar3;
    }
    param_1 = pbVar4 + 1;
    pbVar3 = param_2;
    pbVar4 = param_1;
  }
  goto LAB_08005456;
}


/* 08005472 FUN_08005472 */

char * FUN_08005472(char *param_1,char *param_2,int param_3)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  bool bVar4;
  
  pcVar3 = param_1;
  while (bVar4 = param_3 != 0, param_3 = param_3 + -1, bVar4) {
    cVar1 = *param_2;
    pcVar2 = pcVar3 + 1;
    *pcVar3 = cVar1;
    pcVar3 = pcVar2;
    if (cVar1 != '\0') {
      param_2 = param_2 + 1;
    }
  }
  return param_1;
}


/* 0800549e FUN_0800549e */

int FUN_0800549e(char *param_1)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  
  pcVar3 = param_1;
  do {
    pcVar2 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar2;
  } while (cVar1 != '\0');
  return (int)pcVar2 - (int)(param_1 + 1);
}


/* 080054ac FUN_080054ac */

void FUN_080054ac(int param_1,int param_2,uint param_3)

{
  uint uVar1;
  
  for (uVar1 = 0;
      ((uVar1 < param_3 && (*(char *)(param_1 + uVar1) == *(char *)(param_2 + uVar1))) &&
      (*(char *)(param_1 + uVar1) != '\0')); uVar1 = uVar1 + 1) {
  }
  return;
}


/* 080054ca FUN_080054ca */

uint FUN_080054ca(uint param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  bool bVar10;
  ulonglong uVar11;
  longlong lVar12;
  
  iVar1 = (int)(param_2 ^ param_4) >> 0x1f;
  iVar2 = -iVar1;
  uVar7 = param_3;
  uVar9 = param_4;
  if ((param_2 & 0x7fffffff) <= (param_4 & 0x7fffffff) &&
      (uint)(param_3 <= param_1) <= (param_2 & 0x7fffffff) - (param_4 & 0x7fffffff)) {
    uVar7 = param_1;
    uVar9 = param_2;
    param_2 = param_4;
    param_1 = param_3;
  }
  if ((uVar9 & 0x7fffffff) != 0 || uVar7 != 0) {
    uVar8 = param_2 >> 0x14;
    uVar3 = uVar8 & 0x7ff;
    iVar4 = uVar3 - ((uVar9 << 1) >> 0x15);
    if (iVar4 < 0x40) {
      uVar9 = uVar9 & 0xfffff | 0x100000;
      if (iVar2 != 0) {
        bVar10 = uVar7 != 0;
        uVar7 = -uVar7;
        uVar9 = -(uint)bVar10 - uVar9;
      }
      uVar11 = FUN_080059a2(uVar7,uVar9,0x40 - iVar4);
      uVar6 = (uint)(uVar11 >> 0x20);
      uVar5 = (uint)uVar11;
      lVar12 = FUN_080059e0(uVar7,uVar9,iVar4);
      lVar12 = lVar12 + CONCAT44(param_2,param_1);
      param_1 = (uint)lVar12;
      uVar7 = (uint)((ulonglong)lVar12 >> 0x20);
      if ((param_2 ^ uVar7) >> 0x14 != 0) {
        if (iVar2 == 0) {
          uVar11 = CONCAT44(uVar6 >> 1 | param_1 * -0x80000000,
                            (uint)((uVar11 & 0x100000000) != 0) << 0x1f | uVar5 >> 1);
          param_1 = (uint)((uVar7 + 0x100000 & 1) != 0) << 0x1f | param_1 >> 1;
        }
        else {
          if (iVar4 < 2) {
            uVar7 = FUN_08005a90(param_1,uVar7 + uVar8 * -0x100000 + 0x100000,uVar5,uVar6,0,
                                 (uVar8 & 0x800) << 0x14,uVar3);
            return uVar7;
          }
          param_1 = param_1 * 2 | uVar6 >> 0x1f;
          uVar11 = CONCAT44(uVar6 * 2 + (uint)CARRY4(uVar5,uVar5),uVar5 * 2);
        }
      }
    }
    else {
      uVar11 = CONCAT44(-(uint)(1 < (uint)(iVar1 * -2)),iVar1 * 2 + 1);
      param_1 = param_1 + iVar1;
    }
    if (((longlong)uVar11 < 0) &&
       (param_1 = param_1 + 1,
       (uVar11 & 0x7fffffff) == 0 &&
       (int)(uVar11 >> 0x20) * 2 + (uint)CARRY4((uint)uVar11,(uint)uVar11) == 0)) {
      param_1 = param_1 & 0xfffffffe;
    }
    return param_1;
  }
  return param_1;
}


/* 0800560c FUN_0800560c */

void FUN_0800560c(void)

{
  FUN_080054ca();
  return;
}


/* 08005612 FUN_08005612 */

void FUN_08005612(undefined4 param_1,uint param_2)

{
  FUN_080054ca(param_1,param_2 ^ 0x80000000);
  return;
}


/* 08005618 FUN_08005618 */

void FUN_08005618(uint param_1,uint param_2,uint param_3,uint param_4)

{
  longlong lVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  
  if ((param_1 != 0 || (param_2 & 0x7fffffff) != 0) && (param_3 != 0 || (param_4 & 0x7fffffff) != 0)
     ) {
    uVar6 = (uint)((ulonglong)param_1 * (ulonglong)param_3);
    uVar2 = param_2 & 0xfffff | 0x100000;
    uVar3 = param_4 & 0xfffff | 0x100000;
    uVar4 = param_1 >> 10 | (param_2 & 0xfffff) << 0x16;
    uVar8 = param_3 >> 10 | (param_4 & 0xfffff) << 0x16;
    lVar1 = (ulonglong)uVar4 * (ulonglong)uVar8;
    uVar7 = (uint)lVar1;
    iVar5 = uVar4 * (uVar3 >> 10) + (uVar2 >> 10) * uVar8 + (int)((ulonglong)lVar1 >> 0x20);
    uVar8 = ((param_1 * uVar3 +
             uVar2 * param_3 + (int)((ulonglong)param_1 * (ulonglong)param_3 >> 0x20)) -
            (iVar5 * 0x100000 | uVar7 >> 0xc)) - (uint)(uVar6 < uVar7 * 0x100000);
    uVar4 = param_1 >> 0x1a | uVar2 << 6;
    uVar2 = param_3 >> 0x1a | uVar3 << 6;
    uVar3 = uVar6 + uVar7 * -0x100000 >> 0x14 | uVar8 * 0x1000;
    lVar1 = (ulonglong)uVar4 * (ulonglong)uVar2 +
            (ulonglong)((iVar5 - uVar4 * uVar2) + (uVar8 >> 0x14) + (uint)CARRY4(uVar3,uVar7));
    FUN_08005a90((int)lVar1,(int)((ulonglong)lVar1 >> 0x20),uVar6 * 0x1000,uVar3 + uVar7,0,
                 (param_2 ^ param_4) & 0x80000000,
                 (((param_4 & 0x7fffffff) << 1) >> 0x15) + (((param_2 & 0x7fffffff) << 1) >> 0x15) +
                 -0x3ff);
  }
  return;
}


/* 080056fc FUN_080056fc */

undefined8 FUN_080056fc(uint param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  bool bVar10;
  
  if ((param_1 != 0 || (param_2 & 0x7fffffff) != 0) && (param_3 != 0 || (param_4 & 0x7fffffff) != 0)
     ) {
    uVar5 = param_4 & 0xfffff | 0x100000;
    uVar4 = param_2 & 0xfffff | 0x100000;
    iVar7 = (((param_2 & 0x7fffffff) << 1) >> 0x15) - (((param_4 & 0x7fffffff) << 1) >> 0x15);
    iVar8 = iVar7 + 0x3fd;
    if (uVar5 < uVar4 || uVar4 - uVar5 < (uint)(param_3 <= param_1)) {
      iVar8 = iVar7 + 0x3fe;
    }
    else {
      bVar10 = CARRY4(param_1,param_1);
      param_1 = param_1 * 2;
      uVar4 = uVar4 * 2 + (uint)bVar10;
    }
    if (-1 < iVar8) {
      uVar3 = 0x100000;
      uVar6 = 0;
      uVar9 = 0;
      for (uVar2 = 0; uVar2 != 0 || uVar3 != 0; uVar2 = (uint)(uVar1 != 0) << 0x1f | uVar2 >> 1) {
        if (uVar5 < uVar4 || uVar4 - uVar5 < (uint)(param_3 <= param_1)) {
          bVar10 = param_1 < param_3;
          param_1 = param_1 - param_3;
          uVar4 = (uVar4 - uVar5) - (uint)bVar10;
          uVar6 = uVar6 | uVar2;
          uVar9 = uVar9 | uVar3;
        }
        uVar1 = uVar3 & 1;
        uVar3 = uVar3 >> 1;
        bVar10 = CARRY4(param_1,param_1);
        param_1 = param_1 * 2;
        uVar4 = uVar4 * 2 + (uint)bVar10;
      }
      if (param_1 != 0 || uVar4 != 0) {
        if (param_1 == param_3 && uVar4 == uVar5) {
          param_1 = 0;
          uVar4 = 0x80000000;
        }
        else if (uVar5 < uVar4 || uVar4 - uVar5 < (uint)(param_3 <= param_1)) {
          param_1 = 0xfffffffe;
          uVar4 = 0xffffffff;
        }
        else {
          param_1 = 1;
          uVar4 = 0;
        }
      }
      iVar7 = uVar9 + iVar8 * 0x100000 + ((param_2 ^ param_4) & 0x80000000);
      if ((int)uVar4 < 0) {
        bVar10 = 0xfffffffe < uVar6;
        uVar6 = uVar6 + 1;
        iVar7 = iVar7 + (uint)bVar10;
        if ((param_1 & 0x7fffffff) == 0 && uVar4 * 2 + (uint)CARRY4(param_1,param_1) == 0) {
          uVar6 = uVar6 & 0xfffffffe;
        }
      }
      return CONCAT44(iVar7,uVar6);
    }
  }
  return 0;
}


/* 080057da FUN_080057da */

void FUN_080057da(uint param_1)

{
  uint uVar1;
  
  uVar1 = (int)param_1 >> 0x1f;
  FUN_08005a90((param_1 ^ uVar1) - uVar1,0,0,0,0,uVar1 * -0x80000000,0x433);
  return;
}


/* 080057fc thunk_FUN_080057fe */

void thunk_FUN_080057fe(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}


/* 080057fe FUN_080057fe */

void FUN_080057fe(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}


/* 08005808 FUN_08005808 */

void FUN_08005808(undefined4 param_1)

{
  FUN_08005a90(param_1,0,0,0,0,0,0x433);
  return;
}


/* 08005822 FUN_08005822 */

int FUN_08005822(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = (param_2 << 1) >> 0x15;
  if (uVar2 < 0x3ff) {
    return 0;
  }
  if (uVar2 < 0x434) {
    iVar1 = FUN_080059c0(param_1,param_2 & 0xfffff | 0x100000,-(uVar2 - 0x433));
    return iVar1;
  }
  return param_1 << (uVar2 - 0x433 & 0xff);
}


/* 08005854 FUN_08005854 */

undefined8 FUN_08005854(uint param_1)

{
  uint uVar1;
  
  uVar1 = param_1 & 0x7fffffff;
  if (uVar1 != 0) {
    return CONCAT44(param_1 & 0x80000000 | ((uVar1 >> 0x17) + 0x380) * 0x100000 |
                    (uVar1 << 9) >> 0xc,param_1 << 0x1d);
  }
  return 0;
}


/* 0800587c FUN_0800587c */

int FUN_0800587c(int param_1,int param_2)

{
  if (-1 < param_2) {
    param_1 = -param_1;
  }
  return param_1;
}


/* 080058ac FUN_080058ac */

int FUN_080058ac(int param_1,int param_2)

{
  if (-1 < param_2) {
    param_1 = -param_1;
  }
  return param_1;
}


/* 080058dc FUN_080058dc */

uint FUN_080058dc(uint param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  
  if (param_1 != 0 || (param_2 & 0x7fffffff) != 0) {
    iVar2 = ((param_2 & 0x7fffffff) >> 0x14) - 0x380;
    if (0 < iVar2) {
      uVar1 = (param_1 >> 0x1d | (param_2 & 0xfffff) << 3) + (param_2 & 0x80000000) +
              iVar2 * 0x800000;
      if (-1 < (int)(param_1 * 8)) {
        return uVar1;
      }
      uVar1 = uVar1 + 1;
      if ((param_1 & 0xfffffff) == 0) {
        uVar1 = uVar1 & 0xfffffffe;
      }
      return uVar1;
    }
  }
  return 0;
}


/* 08005914 FUN_08005914 */

int FUN_08005914(uint param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  iVar1 = 0;
  uVar2 = 0x20;
  while (uVar3 = uVar2 - 1, 0 < (int)uVar2) {
    uVar2 = uVar3;
    if (param_2 <= param_1 >> (uVar3 & 0xff)) {
      param_1 = param_1 - (param_2 << (uVar3 & 0xff));
      iVar1 = iVar1 + (1 << (uVar3 & 0xff));
    }
  }
  return iVar1;
}


/* 08005940 FUN_08005940 */

longlong FUN_08005940(uint param_1,int param_2,uint param_3,uint param_4)

{
  longlong lVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  undefined8 uVar6;
  longlong lVar7;
  
  lVar1 = 0;
  iVar3 = 0x40;
  while (iVar4 = iVar3 + -1, 0 < iVar3) {
    uVar6 = FUN_080059c0(param_1,param_2,iVar4);
    uVar2 = (uint)((ulonglong)uVar6 >> 0x20);
    iVar3 = iVar4;
    if (param_4 < uVar2 || uVar2 - param_4 < (uint)(param_3 <= (uint)uVar6)) {
      uVar6 = FUN_080059a2(param_3,param_4,iVar4);
      bVar5 = param_1 < (uint)uVar6;
      param_1 = param_1 - (uint)uVar6;
      param_2 = (param_2 - (int)((ulonglong)uVar6 >> 0x20)) - (uint)bVar5;
      lVar7 = FUN_080059a2(1,0,iVar4);
      lVar1 = lVar7 + lVar1;
    }
  }
  return lVar1;
}


/* 080059a2 FUN_080059a2 */

longlong FUN_080059a2(uint param_1,int param_2,uint param_3)

{
  if (0x1f < (int)param_3) {
    return (ulonglong)(param_1 << (param_3 - 0x20 & 0xff)) << 0x20;
  }
  return CONCAT44(param_2 << (param_3 & 0xff) | param_1 >> (0x20 - param_3 & 0xff),
                  param_1 << (param_3 & 0xff));
}


/* 080059c0 FUN_080059c0 */

ulonglong FUN_080059c0(uint param_1,uint param_2,uint param_3)

{
  if (0x1f < (int)param_3) {
    return (ulonglong)(param_2 >> (param_3 - 0x20 & 0xff));
  }
  return CONCAT44(param_2 >> (param_3 & 0xff),
                  param_1 >> (param_3 & 0xff) | param_2 << (0x20 - param_3 & 0xff));
}


/* 080059e0 FUN_080059e0 */

undefined8 FUN_080059e0(uint param_1,uint param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  
  if ((int)param_3 < 0x20) {
    iVar2 = (int)param_2 >> (param_3 & 0xff);
    uVar1 = param_1 >> (param_3 & 0xff) | param_2 << (0x20 - param_3 & 0xff);
  }
  else {
    uVar1 = (int)param_2 >> (param_3 - 0x20 & 0xff);
    iVar2 = (int)(param_2 | uVar1) >> 0x1f;
  }
  return CONCAT44(iVar2,uVar1);
}


/* 08005a16 FUN_08005a16 */

uint FUN_08005a16(int param_1,uint param_2,int param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = LZCOUNT(param_1);
  uVar1 = param_1 << iVar3;
  if (uVar1 == 0 && param_2 == 0) {
    return uVar1;
  }
  if (param_2 != 0) {
    uVar2 = param_2 << iVar3;
    if (uVar2 != 0) {
      uVar2 = 1;
    }
    uVar1 = uVar1 | uVar2 | param_2 >> (0x20U - iVar3 & 0xff);
  }
  iVar3 = (param_4 - iVar3) + 7;
  if (-1 < iVar3) {
    uVar2 = (uVar1 >> 8) + iVar3 * 0x800000 + param_3;
    if ((int)(uVar1 * 0x1000000) < 0) {
      uVar2 = uVar2 + 1;
      if ((uVar1 & 0x7f) == 0) {
        uVar2 = uVar2 & 0xfffffffe;
      }
      return uVar2;
    }
    return uVar2;
  }
  return 0;
}


/* 08005a90 FUN_08005a90 */

ulonglong FUN_08005a90(undefined4 param_1,int param_2,int param_3,int param_4,uint param_5,
                      int param_6,int param_7)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  ulonglong uVar5;
  undefined8 uVar6;
  longlong lVar7;
  
  if (param_2 == 0) {
    iVar2 = LZCOUNT(param_1) + 0x20;
  }
  else {
    iVar2 = LZCOUNT(param_2);
  }
  uVar5 = FUN_080059a2();
  uVar3 = (uint)(uVar5 >> 0x20);
  if (((uint)uVar5 != 0 || param_3 != 0) || (uVar3 != 0 || param_4 != 0)) {
    if (param_3 != 0 || param_4 != 0) {
      uVar6 = FUN_080059c0(param_3,param_4,0x40 - iVar2);
      lVar7 = FUN_080059a2(param_3,param_4,iVar2);
      uVar5 = CONCAT44(uVar3 | (uint)((ulonglong)uVar6 >> 0x20),
                       (uint)uVar5 | (uint)uVar6 | (uint)(lVar7 != 0));
    }
    uVar3 = (uint)(uVar5 >> 0xb);
    iVar2 = (param_7 - iVar2) + 10;
    if (-1 < iVar2) {
      uVar1 = uVar3 + param_5;
      iVar2 = iVar2 * 0x100000 + (int)((uVar5 >> 0xb) >> 0x20) + param_6 +
              (uint)CARRY4(uVar3,param_5);
      if ((int)uVar5 * 0x200000 < 0) {
        bVar4 = 0xfffffffe < uVar1;
        uVar1 = uVar1 + 1;
        iVar2 = iVar2 + (uint)bVar4;
        if ((uVar5 & 0x3ff) == 0) {
          uVar1 = uVar1 & 0xfffffffe;
        }
      }
      return CONCAT44(iVar2,uVar1);
    }
    uVar5 = 0;
  }
  return uVar5;
}


/* 08005b2c FUN_08005b2c */

undefined8 FUN_08005b2c(int param_1,uint param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  
  if ((param_2 & 0x7fffffff) != 0 || param_1 != 0) {
    uVar2 = (param_2 << 1) >> 0x15;
    iVar1 = -(uint)(uVar2 != 0);
    iVar3 = (int)param_3 >> 0x1f;
    bVar4 = -uVar2 < param_3;
    if ((int)((iVar1 - iVar3) - (uint)bVar4) < 0 !=
        (SBORROW4(iVar1,iVar3) != SBORROW4(iVar1 - iVar3,(uint)bVar4))) {
      return CONCAT44(param_2 + param_3 * 0x100000,param_1);
    }
    param_1 = 0;
    param_2 = 0;
  }
  return CONCAT44(param_2,param_1);
}


/* 08005b5a FUN_08005b5a */

undefined8 FUN_08005b5a(uint param_1,uint param_2)

{
  longlong lVar1;
  longlong lVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  bool bVar9;
  longlong lVar10;
  
  uVar6 = -param_1;
  if ((int)(uint)(param_1 != 0) <= (int)-param_2) {
    return 0;
  }
  uVar5 = (param_2 << 1) >> 0x15;
  uVar7 = param_2 & 0xfffff | 0x100000;
  if ((uVar5 & 1) == 0) {
    bVar9 = CARRY4(param_1,param_1);
    param_1 = param_1 * 2;
    uVar7 = uVar7 * 2 + (uint)bVar9;
    uVar5 = uVar5 - 1;
  }
  lVar2 = 0;
  iVar8 = 0;
  do {
    lVar10 = FUN_080059c0(0,0x100000,iVar8,uVar6);
    lVar1 = lVar10 + lVar2 + lVar2;
    uVar6 = (uint)lVar1;
    uVar3 = (uint)((ulonglong)lVar1 >> 0x20);
    if (uVar3 < uVar7 || uVar7 - uVar3 < (uint)(uVar6 <= param_1)) {
      bVar9 = param_1 < uVar6;
      param_1 = param_1 - uVar6;
      uVar7 = (uVar7 - uVar3) - (uint)bVar9;
      lVar2 = lVar10 + lVar2;
    }
    iVar4 = (int)((ulonglong)lVar2 >> 0x20);
    uVar3 = (uint)lVar2;
    bVar9 = CARRY4(param_1,param_1);
    param_1 = param_1 * 2;
    iVar8 = iVar8 + 1;
    uVar7 = uVar7 * 2 + (uint)bVar9;
  } while (iVar8 < 0x35);
  uVar6 = iVar4 * 2 + (uint)CARRY4(uVar3,uVar3);
  if (uVar7 < uVar6 || uVar6 - uVar7 < (uint)(param_1 <= uVar3 * 2)) {
    uVar6 = 0;
    iVar8 = 0;
  }
  else {
    uVar6 = 0xffffffff;
    iVar8 = -1;
  }
  iVar4 = iVar4 + (((int)uVar5 >> 1) + 0x1ff) * 0x100000;
  if (iVar8 < 0) {
    bVar9 = 0xfffffffe < uVar3;
    uVar3 = uVar3 + 1;
    iVar4 = iVar4 + (uint)bVar9;
    if ((uVar6 & 0x7fffffff) == 0 && iVar8 * 2 + (uint)CARRY4(uVar6,uVar6) == 0) {
      uVar3 = uVar3 & 0xfffffffe;
    }
  }
  return CONCAT44(iVar4,uVar3);
}


/* 08005bfc FUN_08005bfc */

void FUN_08005bfc(undefined4 param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = (param_2 << 1) >> 0x15;
  uVar1 = param_2 & 0xfffff | 0x100000;
  if (uVar2 < 0x3ff) {
    return;
  }
  if (uVar2 < 0x434) {
    FUN_080059c0(param_1,uVar1,-(uVar2 - 0x433));
    return;
  }
  FUN_080059a2(param_1,uVar1);
  return;
}


/* 08005c2c FUN_08005c2c */

void FUN_08005c2c(void)

{
  undefined4 *puVar1;
  int iVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte *extraout_r2;
  byte *pbVar5;
  byte *pbVar6;
  uint uVar7;
  undefined4 *puVar8;
  uint uVar9;
  byte *pbVar10;
  
  puVar1 = puRam08005c4c;
  for (puVar8 = puRam08005c48; puVar8 < puVar1; puVar8 = puVar8 + 4) {
    (*(code *)puVar8[3])(*puVar8,puVar8[1],puVar8[2]);
  }
  iVar2 = thunk_FUN_080115f4();
  pbVar5 = extraout_r2;
  do {
    pbVar10 = (byte *)(iVar2 + 0x14);
    pbVar4 = (byte *)0x0;
    do {
      uVar9 = (uint)*pbVar10;
      uVar7 = uVar9 & 7;
      pbVar3 = pbVar10 + 1;
      if ((*pbVar10 & 7) == 0) {
        pbVar3 = pbVar10 + 2;
        uVar7 = (uint)pbVar10[1];
      }
      pbVar6 = (byte *)((int)uVar9 >> 4);
      if (pbVar6 == (byte *)0x0) {
        pbVar6 = (byte *)(uint)*pbVar3;
        pbVar3 = pbVar3 + 1;
      }
      while (uVar7 = uVar7 - 1, uVar7 != 0) {
        *pbVar4 = *pbVar3;
        pbVar3 = pbVar3 + 1;
        pbVar4 = pbVar4 + 1;
      }
      if ((int)(uVar9 << 0x1c) < 0) {
        pbVar10 = pbVar3 + 1;
        pbVar6 = pbVar6 + 2;
        pbVar3 = pbVar4 + -(uint)*pbVar3;
        while (pbVar6 = pbVar6 + -1, -1 < (int)pbVar6) {
          *pbVar4 = *pbVar3;
          pbVar4 = pbVar4 + 1;
          pbVar3 = pbVar3 + 1;
        }
      }
      else {
        while (pbVar6 = pbVar6 + -1, pbVar10 = pbVar3, -1 < (int)pbVar6) {
          *pbVar4 = 0;
          pbVar4 = pbVar4 + 1;
        }
      }
    } while (pbVar4 < pbVar5);
    iVar2 = 0;
    pbVar5 = pbVar6;
  } while( true );
}


/* 08005c50 FUN_08005c50 */

void FUN_08005c50(byte *param_1,byte *param_2,int param_3)

{
  byte *pbVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  uint uVar6;
  code *UNRECOVERED_JUMPTABLE;
  
  pbVar5 = param_2 + param_3;
  do {
    uVar6 = (uint)*param_1;
    uVar4 = uVar6 & 7;
    pbVar1 = param_1 + 1;
    if ((*param_1 & 7) == 0) {
      pbVar1 = param_1 + 2;
      uVar4 = (uint)param_1[1];
    }
    uVar2 = (int)uVar6 >> 4;
    if (uVar2 == 0) {
      uVar2 = (uint)*pbVar1;
      pbVar1 = pbVar1 + 1;
    }
    while (uVar4 = uVar4 - 1, uVar4 != 0) {
      *param_2 = *pbVar1;
      pbVar1 = pbVar1 + 1;
      param_2 = param_2 + 1;
    }
    if ((int)(uVar6 << 0x1c) < 0) {
      param_1 = pbVar1 + 1;
      iVar3 = uVar2 + 2;
      pbVar1 = param_2 + -(uint)*pbVar1;
      while (iVar3 = iVar3 + -1, -1 < iVar3) {
        *param_2 = *pbVar1;
        param_2 = param_2 + 1;
        pbVar1 = pbVar1 + 1;
      }
    }
    else {
      while (uVar2 = uVar2 - 1, param_1 = pbVar1, -1 < (int)uVar2) {
        *param_2 = 0;
        param_2 = param_2 + 1;
      }
    }
  } while (param_2 < pbVar5);
                    /* WARNING: Could not recover jumptable at 0x08005ca4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(0);
  return;
}


/* 08005ca6 FUN_08005ca6 */

void FUN_08005ca6(uint *param_1,uint param_2)

{
  *param_1 = ~param_2 & 0x7f;
  return;
}


/* 08005cae FUN_08005cae */

void FUN_08005cae(int param_1,undefined4 param_2)

{
  if (param_1 == 0) {
    FUN_0800a230(0x100,0);
    FUN_0800a218(param_2);
  }
  else {
    FUN_0800a230(param_2,1);
    FUN_0800a218(0);
  }
  return;
}


/* 08005cd8 FUN_08005cd8 */

void FUN_08005cd8(int param_1,uint param_2)

{
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & 0xffff8fff | param_2;
  return;
}


/* 08005ce8 FUN_08005ce8 */

void FUN_08005ce8(int param_1,int param_2,int param_3,uint param_4)

{
  uint uVar1;
  
  if (param_2 == 0x12) {
    *(uint *)(param_1 + 0x5c) = *(uint *)(param_1 + 0x5c) & 0xfffffff8 | param_4;
  }
  else if (param_2 < 10) {
    *(uint *)(param_1 + 0x10) =
         *(uint *)(param_1 + 0x10) & ~(7 << (param_2 * 3 & 0xffU)) |
         param_4 << (param_2 * 3 & 0xffU);
  }
  else {
    *(uint *)(param_1 + 0xc) =
         *(uint *)(param_1 + 0xc) & ~(7 << ((param_2 + -10) * 3 & 0xffU)) |
         param_4 << ((param_2 + -10) * 3 & 0xffU);
  }
  uVar1 = (*(uint *)(param_1 + 0x38) << 10) >> 0x1e;
  *(uint *)(param_1 + 0x38) =
       *(uint *)(param_1 + 0x38) & ~(0x1f << (((param_3 + 3) - (uVar1 + 1)) * 5 & 0xff)) |
       param_2 << (((param_3 + 3) - (uVar1 + 1)) * 5 & 0xff);
  return;
}


/* 08005d7a FUN_08005d7a */

void FUN_08005d7a(int param_1,int param_2)

{
  *(uint *)(param_1 + 0x38) = *(uint *)(param_1 + 0x38) & 0xffcfffff | (param_2 + -1) * 0x100000;
  return;
}


/* 08005d92 FUN_08005d92 */

void FUN_08005d92(int param_1,int param_2,int param_3,uint param_4)

{
  if (param_2 == 0x12) {
    *(uint *)(param_1 + 0x5c) = *(uint *)(param_1 + 0x5c) & 0xfffffff8 | param_4;
  }
  if (param_2 < 10) {
    *(uint *)(param_1 + 0x10) =
         *(uint *)(param_1 + 0x10) & ~(7 << (param_2 * 3 & 0xffU)) |
         param_4 << (param_2 * 3 & 0xffU);
  }
  else {
    *(uint *)(param_1 + 0xc) =
         *(uint *)(param_1 + 0xc) & ~(7 << ((param_2 + -10) * 3 & 0xffU)) |
         param_4 << ((param_2 + -10) * 3 & 0xffU);
  }
  if (param_3 < 7) {
    *(uint *)(param_1 + 0x34) =
         *(uint *)(param_1 + 0x34) & ~(0x1f << ((param_3 + -1) * 5 & 0xffU)) |
         param_2 << ((param_3 + -1) * 5 & 0xffU);
  }
  else if (param_3 < 0xd) {
    *(uint *)(param_1 + 0x30) =
         *(uint *)(param_1 + 0x30) & ~(0x1f << ((param_3 + -7) * 5 & 0xffU)) |
         param_2 << ((param_3 + -7) * 5 & 0xffU);
  }
  else {
    *(uint *)(param_1 + 0x2c) =
         *(uint *)(param_1 + 0x2c) & ~(0x1f << ((param_3 + -0xd) * 5 & 0xffU)) |
         param_2 << ((param_3 + -0xd) * 5 & 0xffU);
  }
  return;
}


/* 08005e58 FUN_08005e58 */

void FUN_08005e58(int param_1)

{
  if (param_1 == DAT_08005e74) {
    FUN_0800a274(DAT_08005e74 >> 0x12,1);
    FUN_0800a274(param_1 >> 0x12,0);
  }
  return;
}


/* 08005e78 FUN_08005e78 */

void FUN_08005e78(int param_1,int param_2)

{
  if (param_2 == 0) {
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & 0xfffffffe;
  }
  else {
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 1;
  }
  return;
}


/* 08005e8e FUN_08005e8e */

void FUN_08005e8e(int param_1,int param_2)

{
  if (param_2 == 0) {
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & 0xfffffeff;
  }
  else {
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 0x100;
  }
  return;
}


/* 08005ea4 FUN_08005ea4 */

void FUN_08005ea4(int param_1,int param_2)

{
  if (param_2 == 0) {
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & 0xffafffff;
  }
  else {
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 0x500000;
  }
  return;
}


/* 08005eba FUN_08005eba */

void FUN_08005eba(int param_1,int param_2)

{
  if (param_2 == 0) {
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & 0xffdf7fff;
  }
  else {
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 0x208000;
  }
  return;
}


/* 08005ed0 FUN_08005ed0 */

bool FUN_08005ed0(int param_1)

{
  return *(int *)(param_1 + 0x54) == 0 && (*(uint *)(param_1 + 8) & 4) != 0;
}


/* 08005eea FUN_08005eea */

bool FUN_08005eea(uint *param_1,uint param_2)

{
  return (*param_1 & param_2) != 0;
}


/* 08005efc FUN_08005efc */

bool FUN_08005efc(int param_1,uint param_2)

{
  return (*(uint *)(param_1 + 0x58) & param_2) != 0;
}


/* 08005f0e FUN_08005f0e */

uint FUN_08005f0e(int param_1,int param_2)

{
  return *(uint *)(param_2 + 0x28 + param_1) & 0xffff;
}


/* 08005f2c FUN_08005f2c */

void FUN_08005f2c(int param_1,byte *param_2)

{
  *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) & DAT_08005f70 | (uint)*param_2 << 8;
  *(uint *)(param_1 + 8) =
       *(uint *)(param_1 + 8) & DAT_08005f74 |
       *(uint *)(param_2 + 8) | *(uint *)(param_2 + 4) | (uint)param_2[1] << 1;
  *(uint *)(param_1 + 0x2c) =
       *(uint *)(param_1 + 0x2c) & 0xff0fffff | (param_2[0xc] - 1 & 0xff) << 0x14;
  return;
}


/* 08005f78 FUN_08005f78 */

void FUN_08005f78(int param_1)

{
  if (*(int *)(param_1 + 0x54) == 0) {
    *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 4;
  }
  return;
}


/* 08005f88 FUN_08005f88 */

void FUN_08005f88(void)

{
  uint *puVar1;
  uint uVar2;
  
  puVar1 = DAT_08005fe4;
  *DAT_08005fe4 = *DAT_08005fe4 & 0xfdffffff;
  *puVar1 = *puVar1 | 0x2000000;
  puVar1 = DAT_08005fe8;
  *DAT_08005fe8 = *DAT_08005fe8 & 0xfffff9ff;
  *puVar1 = *puVar1 | 0x400;
  do {
  } while ((DAT_08005fe8[4] & 2) != 0);
  for (uVar2 = 0; uVar2 < 0x2a; uVar2 = uVar2 + 1) {
  }
  do {
  } while ((DAT_08005fe8[4] & 2) != 2);
  return;
}


/* 08005fec FUN_08005fec */

void FUN_08005fec(undefined4 param_1,int param_2)

{
  *(undefined4 *)(param_2 + 4) = param_1;
  return;
}


/* 08005ff0 FUN_08005ff0 */

void FUN_08005ff0(undefined4 param_1,int param_2)

{
  *(undefined4 *)(param_2 + 4) = param_1;
  return;
}


/* 08005ff4 FUN_08005ff4 */

void FUN_08005ff4(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 4) = param_2;
  return;
}


/* 08005ff8 FUN_08005ff8 */

void FUN_08005ff8(void)

{
  return;
}


/* 08005ffa FUN_08005ffa */

void FUN_08005ffa(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x28) = param_2;
  return;
}


/* 08005ffe FUN_08005ffe */

void FUN_08005ffe(void)

{
  return;
}


/* 0800920c FUN_0800920c */

/* WARNING: Heritage AFTER dead removal. Example location: s1 : 0x08009252 */
/* WARNING: Restarted to delay deadcode elimination for space: register */

void FUN_0800920c(float param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 extraout_s1;
  undefined4 extraout_s1_00;
  undefined4 extraout_s1_01;
  undefined4 extraout_s1_02;
  undefined8 uVar3;
  undefined8 uVar4;
  
  uVar3 = FUN_08005854(DAT_08009310);
  uVar1 = FUN_08005854();
  uVar2 = FUN_0800b500(uVar1,param_2,(int)DAT_08009318);
  uVar1 = FUN_08005854();
  uVar1 = FUN_0800b500(uVar1,extraout_s1,(int)DAT_08009318);
  uVar1 = FUN_080054ca(uVar1,extraout_s1_00,uVar2,extraout_s1);
  uVar1 = FUN_0800c150(uVar1);
  uVar4 = FUN_08005854(param_1 * -1.0);
  uVar1 = FUN_080056fc((int)uVar4,(int)((ulonglong)uVar4 >> 0x20),uVar1,extraout_s1_01);
  uVar1 = FUN_0800b210(uVar1);
  uVar4 = FUN_08005618(uVar1,extraout_s1_02,(int)DAT_08009320,(int)((ulonglong)DAT_08009320 >> 0x20)
                      );
  FUN_080056fc((int)uVar4,(int)((ulonglong)uVar4 >> 0x20),(int)uVar3,(int)((ulonglong)uVar3 >> 0x20)
              );
  FUN_080058dc();
  return;
}


/* 08009328 FUN_08009328 */

void FUN_08009328(void)

{
  int iVar1;
  
  iVar1 = FUN_0800949c(0x20,DAT_08009374);
  if (iVar1 != 0) {
    FUN_08005fec(0x20,DAT_08009374);
    FUN_0800a49e(DAT_08009378,2,0);
    FUN_0800a486(DAT_08009378,0);
    FUN_0800a474(DAT_08009378,0);
    FUN_0800a486(DAT_08009378,1);
    *DAT_0800937c = 1;
    *DAT_08009380 = 1;
    FUN_080098e2(DAT_08009384,0x400);
  }
  return;
}


/* 08009388 FUN_08009388 */

void FUN_08009388(uint *param_1,uint param_2,int param_3)

{
  if (param_3 == 0) {
    *param_1 = *param_1 & ~param_2;
  }
  else {
    *param_1 = *param_1 | param_2;
  }
  return;
}


/* 0800939c FUN_0800939c */

void FUN_0800939c(uint *param_1)

{
  *param_1 = *param_1 & 0xfffe;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  if (param_1 == DAT_08009480) {
    DAT_08009480[-1] = DAT_08009480[-1] | 0xf;
  }
  else if (param_1 == DAT_08009480 + 5) {
    DAT_08009480[-1] = DAT_08009480[-1] | 0xf0;
  }
  else if (param_1 == DAT_08009480 + 10) {
    DAT_08009480[-1] = DAT_08009480[-1] | 0xf00;
  }
  else if (param_1 == DAT_08009480 + 0xf) {
    DAT_08009480[-1] = DAT_08009480[-1] | 0xf000;
  }
  else if (param_1 == DAT_08009480 + 0x14) {
    DAT_08009480[-1] = DAT_08009480[-1] | 0xf0000;
  }
  else if (param_1 == DAT_08009480 + 0x19) {
    DAT_08009480[-1] = DAT_08009480[-1] | 0xf00000;
  }
  else if (param_1 == DAT_08009480 + 0x1e) {
    DAT_08009480[-1] = DAT_08009480[-1] | 0xf000000;
  }
  else if (param_1 == DAT_08009480 + 0x23) {
    DAT_08009480[-1] = DAT_08009480[-1] | 0xf0000000;
  }
  return;
}


/* 08009484 FUN_08009484 */

void FUN_08009484(uint *param_1,int param_2)

{
  if (param_2 == 0) {
    *param_1 = *param_1 & 0xfffe;
  }
  else {
    *param_1 = *param_1 | 1;
  }
  return;
}


/* 0800949c FUN_0800949c */

bool FUN_0800949c(uint param_1,uint *param_2)

{
  return (*param_2 & param_1) != 0;
}


/* 080094b4 FUN_080094b4 */

bool FUN_080094b4(uint param_1,uint *param_2)

{
  return (*param_2 & param_1) != 0;
}


/* 080094cc FUN_080094cc */

void FUN_080094cc(uint *param_1,uint *param_2)

{
  *param_1 = *param_1 & 0xffff800f |
             param_2[2] | param_2[8] | param_2[4] | param_2[5] | param_2[6] | param_2[7] |
             param_2[9] | param_2[10];
  param_1[1] = param_2[3];
  param_1[2] = *param_2;
  param_1[3] = param_2[1];
  return;
}


/* 08009508 FUN_08009508 */

void FUN_08009508(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  if (param_4 == 0) {
    *(undefined4 *)(param_3 + 0x10) = 0;
  }
  else {
    *(undefined4 *)(param_3 + 0x10) = param_1;
  }
  return;
}


/* 08009518 FUN_08009518 */

void FUN_08009518(undefined4 param_1)

{
  *DAT_08009520 = param_1;
  return;
}


/* 08009524 FUN_08009524 */

void FUN_08009524(uint param_1)

{
  *(uint *)(DAT_08009530 + 0xc) = *(uint *)(DAT_08009530 + 0xc) | param_1;
  return;
}


/* 08009534 FUN_08009534 */

undefined8 FUN_08009534(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_8;
  
  iVar2 = 0;
  local_8 = 0;
  uVar1 = 0;
  if ((*DAT_0800957c & 2) == 0) {
    *DAT_0800957c = *DAT_0800957c | 1;
    do {
      local_8 = local_8 + 1;
      if ((int)(*DAT_0800957c << 0x1e) < 0) break;
    } while (local_8 != 0x500);
    iVar2 = -((int)(*DAT_0800957c << 0x1e) >> 0x1f);
    if (iVar2 == 0) {
      uVar1 = 1;
    }
  }
  return CONCAT44(iVar2,uVar1);
}


/* 08009580 FUN_08009580 */

int FUN_08009580(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  FUN_08009524(0x7c);
  iVar2 = FUN_080096a8(0xb0000);
  iVar1 = DAT_080095d0;
  if (iVar2 == 6) {
    *(uint *)(DAT_080095d0 + 0x10) = *(uint *)(DAT_080095d0 + 0x10) | 2;
    *(undefined4 *)(iVar1 + 0x14) = param_1;
    *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) | 0x40;
    iVar2 = FUN_080096a8(0xb0000);
    *(uint *)(DAT_080095d0 + 0x10) = *(uint *)(DAT_080095d0 + 0x10) & 0x3ffd;
  }
  return iVar2;
}


/* 080095d4 FUN_080095d4 */

undefined4 FUN_080095d4(void)

{
  undefined4 uVar1;
  
  if ((*(uint *)(DAT_08009620 + 0xc) & 1) == 0) {
    if ((*(uint *)(DAT_08009620 + 0xc) & 4) == 0) {
      if ((*(uint *)(DAT_08009620 + 0xc) & 8) == 0) {
        if ((*(uint *)(DAT_08009620 + 0xc) & 0x10) == 0) {
          if ((*(uint *)(DAT_08009620 + 0xc) & 0x40) == 0) {
            uVar1 = 6;
          }
          else {
            uVar1 = 7;
          }
        }
        else {
          uVar1 = 5;
        }
      }
      else {
        uVar1 = 4;
      }
    }
    else {
      uVar1 = 3;
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}


/* 08009624 FUN_08009624 */

void FUN_08009624(void)

{
  *(uint *)(DAT_08009634 + 0x10) = *(uint *)(DAT_08009634 + 0x10) | 0x80;
  return;
}


/* 08009638 FUN_08009638 */

int FUN_08009638(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  
  if (((uint)param_1 & 3) == 0) {
    FUN_08009524(0x7c);
    iVar1 = FUN_080096a8(0x2000);
    if (iVar1 == 6) {
      *(uint *)(DAT_0800968c + 0x10) = *(uint *)(DAT_0800968c + 0x10) | 1;
      *param_1 = param_2;
      iVar1 = FUN_080096a8(0x2000);
      *(uint *)(DAT_0800968c + 0x10) = *(uint *)(DAT_0800968c + 0x10) & 0x3ffe;
    }
  }
  else {
    iVar1 = 9;
  }
  return iVar1;
}


/* 08009690 FUN_08009690 */

void FUN_08009690(void)

{
  int iVar1;
  
  iVar1 = DAT_080096a0;
  *(undefined4 *)(DAT_080096a0 + 4) = DAT_0800969c;
  *(undefined4 *)(iVar1 + 4) = DAT_080096a4;
  return;
}


/* 080096a8 FUN_080096a8 */

int FUN_080096a8(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int extraout_r2;
  int extraout_r2_00;
  int iVar2;
  
  iVar1 = FUN_080095d4(param_1,param_2,param_1,6);
  iVar2 = extraout_r2;
  while ((iVar1 == 1 && (iVar2 != 0))) {
    iVar1 = FUN_080095d4();
    iVar2 = extraout_r2_00 + -1;
  }
  if (iVar2 == 0) {
    iVar1 = 10;
  }
  return iVar1;
}


/* 080096d0 FUN_080096d0 */

uint FUN_080096d0(uint *param_1,ushort *param_2)

{
  uint *puVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = 0;
  for (uVar4 = 0; (int)(uint)*param_2 >> (uVar4 & 0xff) != 0; uVar4 = uVar4 + 1) {
    if (((uint)*param_2 & 1 << (uVar4 & 0xff)) != 0) {
      uVar3 = uVar4 << 1;
      if ((((*(int *)(param_2 + 4) == 2) || (*(int *)(param_2 + 4) == 0x12)) ||
          (*(int *)(param_2 + 4) == 0)) || (*(int *)(param_2 + 4) == 3)) {
        if ((uVar4 & 8) == 0) {
          param_1[8] = param_1[8] & ~(0xf << ((uVar4 << 0x1d) >> 0x1b)) |
                       *(int *)(param_2 + 6) << ((uVar4 << 0x1d) >> 0x1b);
        }
        else {
          param_1[9] = param_1[9] & ~(0xf << ((uVar4 << 0x1d) >> 0x1b)) |
                       *(int *)(param_2 + 6) << ((uVar4 << 0x1d) >> 0x1b);
        }
      }
      *param_1 = *param_1 & ~(3 << (uVar3 & 0xff)) | ((byte)param_2[4] & 0xf) << (uVar3 & 0xff);
      param_1[3] = param_1[3] & ~(3 << (uVar3 & 0xff)) | ((byte)param_2[2] & 3) << (uVar3 & 0xff);
      if (((param_2[4] & 3) != 0) && (*(int *)(param_2 + 4) != 3)) {
        param_1[0xb] = param_1[0xb] & ~(3 << (uVar3 & 0xff)) |
                       ((byte)param_2[1] & 3) << (uVar3 & 0xff);
      }
      uVar3 = param_1[2] & ~(1 << (uVar4 & 0xff)) |
              (*(byte *)((int)param_2 + 3) & 1) << (uVar4 & 0xff);
      param_1[2] = uVar3;
      if ((char)param_2[2] == '\x02') {
        param_1[10] = param_1[10] | 1 << (uVar4 & 0xff);
      }
      else if ((char)param_2[2] == '\x01') {
        param_1[6] = param_1[6] | 1 << (uVar4 & 0xff);
      }
      if (((*(int *)(param_2 + 4) == 1) || (*(int *)(param_2 + 4) == 2)) ||
         ((*(int *)(param_2 + 4) == 0x11 || (*(int *)(param_2 + 4) == 0x12)))) {
        uVar3 = param_1[1] & ~(1 << (uVar4 & 0xff)) |
                (((uint)(byte)param_2[4] << 0x1b) >> 0x1f) << (uVar4 & 0xff);
        param_1[1] = uVar3;
      }
      puVar1 = DAT_080098b4;
      if ((*(uint *)(param_2 + 4) & 0x10000000) != 0) {
        uVar3 = *DAT_080098b4 & ~(1 << (uVar4 & 0xff));
        if ((*(uint *)(param_2 + 4) & 0x10000) == 0x10000) {
          uVar3 = uVar3 | 1 << (uVar4 & 0xff);
        }
        *DAT_080098b4 = uVar3;
        puVar2 = DAT_080098b4;
        uVar3 = puVar1[1] & ~(1 << (uVar4 & 0xff));
        if ((*(uint *)(param_2 + 4) & 0x20000) == 0x20000) {
          uVar3 = uVar3 | 1 << (uVar4 & 0xff);
        }
        DAT_080098b4[1] = uVar3;
        puVar1 = DAT_080098b4;
        uVar3 = puVar2[2] & ~(1 << (uVar4 & 0xff));
        if ((*(uint *)(param_2 + 4) & 0x100000) == 0x100000) {
          uVar3 = uVar3 | 1 << (uVar4 & 0xff);
        }
        DAT_080098b4[2] = uVar3;
        uVar3 = puVar1[3] & ~(1 << (uVar4 & 0xff));
        if ((*(uint *)(param_2 + 4) & 0x200000) == 0x200000) {
          uVar3 = uVar3 | 1 << (uVar4 & 0xff);
        }
        DAT_080098b4[3] = uVar3;
      }
    }
  }
  return uVar3;
}


/* 080098b8 FUN_080098b8 */

void FUN_080098b8(undefined2 *param_1)

{
  *param_1 = 0xffff;
  *(undefined1 *)((int)param_1 + 3) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 6) = 0xf;
  *(undefined1 *)(param_1 + 2) = 0;
  *(undefined1 *)(param_1 + 1) = 0;
  return;
}


/* 080098d0 FUN_080098d0 */

bool FUN_080098d0(int param_1,uint param_2)

{
  return (*(uint *)(param_1 + 0x10) & param_2) != 0;
}


/* 080098e2 FUN_080098e2 */

void FUN_080098e2(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x18) = param_2;
  return;
}


/* 080098e6 thunk_FUN_080098e8 */

void thunk_FUN_080098e8(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}


/* 080098e8 FUN_080098e8 */

void FUN_080098e8(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}


/* 080098ec FUN_080098ec */

void FUN_080098ec(undefined4 param_1)

{
  *(undefined4 *)(DAT_080098f4 + 8) = param_1;
  return;
}


/* 080098f8 FUN_080098f8 */

void FUN_080098f8(void)

{
  *DAT_08009904 = 0xcccc;
  return;
}


/* 08009908 FUN_08009908 */

void FUN_08009908(void)

{
  FUN_08009974();
  return;
}


/* 08009910 FUN_08009910 */

void FUN_08009910(undefined4 param_1)

{
  undefined2 uVar1;
  int iVar2;
  undefined8 uVar3;
  
  FUN_0800a2d4(1);
  do {
    iVar2 = FUN_0800a438(0x61);
  } while (iVar2 == 0);
  FUN_08009990(0x5555);
  FUN_08009984(3);
  uVar3 = FUN_08005808(param_1);
  FUN_08005618((int)uVar3,(int)((ulonglong)uVar3 >> 0x20),(int)DAT_0800996c,
               (int)((ulonglong)DAT_0800996c >> 0x20));
  uVar1 = FUN_08005822();
  FUN_080098ec(uVar1);
  FUN_08009974();
  FUN_080098f8();
  return;
}


/* 08009974 FUN_08009974 */

void FUN_08009974(void)

{
  *DAT_08009980 = 0xaaaa;
  return;
}


/* 08009984 FUN_08009984 */

void FUN_08009984(undefined4 param_1)

{
  *(undefined4 *)(DAT_0800998c + 4) = param_1;
  return;
}


/* 08009990 FUN_08009990 */

void FUN_08009990(undefined4 param_1)

{
  *DAT_08009998 = param_1;
  return;
}


/* 0800999c FUN_0800999c */

void FUN_0800999c(int param_1)

{
  *(undefined4 *)(param_1 + 0x30) = **(undefined4 **)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x34) = **(undefined4 **)(param_1 + 0x20);
  if (*(float *)(param_1 + 0x30) <= *(float *)(param_1 + 0x40)) {
    if (*(float *)(param_1 + 0x30) < *(float *)(param_1 + 0x3c)) {
      *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x3c);
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x40);
  }
  return;
}


/* 080099e8 FUN_080099e8 */

void FUN_080099e8(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  FUN_0800a0dc(0x2a);
  FUN_0800a0bc(param_1);
  FUN_0800a0bc(param_3);
  FUN_0800a0dc(0x2b);
  FUN_0800a0bc(param_2);
  FUN_0800a0bc(param_4);
  FUN_0800a0dc(0x2c);
  return;
}


/* 08009a24 FUN_08009a24 */

void FUN_08009a24(uint param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  
  if (*(char *)(DAT_08009a5c + 1) == '\0') {
    uVar1 = 0x27 - param_2 & 0xffff;
    param_4 = param_1;
  }
  else {
    uVar1 = param_3;
    if (*(char *)(DAT_08009a5c + 1) == '\x01') {
      uVar1 = param_2;
      param_4 = 0x9f - param_1 & 0xffff;
    }
  }
  *(short *)(DAT_08009a60 + (uVar1 + param_4 * 0x28) * 2) = (short)param_3;
  return;
}


/* 08009a64 FUN_08009a64 */

void FUN_08009a64(void)

{
  undefined2 local_28;
  undefined2 local_26;
  undefined2 local_24;
  undefined2 local_22;
  undefined2 local_20;
  undefined2 local_1e;
  undefined2 local_1c;
  undefined2 local_1a;
  undefined2 local_18;
  undefined2 local_14;
  undefined1 local_12;
  undefined1 local_11;
  undefined4 local_c;
  undefined4 local_8;
  
  FUN_0800a2b4(0x2c,1);
  FUN_0800a2b4(0x1001,1);
  local_14 = 0x440;
  local_c = 1;
  local_11 = 0;
  local_12 = 0x11;
  FUN_080096d0(DAT_08009b4c,&local_14);
  FUN_08005ffa(DAT_08009b4c,0x40);
  FUN_080098e2(DAT_08009b4c,0x400);
  local_14 = 1;
  FUN_080096d0(DAT_08009b50,&local_14);
  FUN_080098e2(DAT_08009b50,1);
  local_14 = 0x28;
  FUN_080096d0(DAT_08009b54,&local_14);
  FUN_080098e2(DAT_08009b54,0x28);
  local_14 = 8;
  local_c = 2;
  local_8 = 1;
  FUN_080096d0(DAT_08009b54,&local_14);
  local_14 = 0x20;
  local_8 = 0;
  FUN_080096d0(DAT_08009b54,&local_14);
  local_28 = 0xc000;
  local_26 = 0x104;
  local_24 = 0;
  local_22 = 2;
  local_20 = 1;
  local_1e = 0x200;
  local_1c = 0;
  local_1a = 0;
  local_18 = 7;
  FUN_0800a4c6(DAT_08009b58,&local_28);
  FUN_0800a486(DAT_08009b58,1);
  return;
}


/* 08009b5c FUN_08009b5c */

void FUN_08009b5c(void)

{
  FUN_08009a64();
  FUN_0800f418(100);
  FUN_0800f418(100);
  FUN_0800a0dc(0xfe);
  FUN_0800a0dc(0xef);
  FUN_0800a0dc(0x80);
  FUN_0800a0ce(0xff);
  FUN_0800a0dc(0x81);
  FUN_0800a0ce(0xff);
  FUN_0800a0dc(0x82);
  FUN_0800a0ce(0xff);
  FUN_0800a0dc(0x83);
  FUN_0800a0ce(0xff);
  FUN_0800a0dc(0x84);
  FUN_0800a0ce(0xff);
  FUN_0800a0dc(0x85);
  FUN_0800a0ce(0xff);
  FUN_0800a0dc(0x86);
  FUN_0800a0ce(0xff);
  FUN_0800a0dc(0x87);
  FUN_0800a0ce(0xff);
  FUN_0800a0dc(0x88);
  FUN_0800a0ce(0xff);
  FUN_0800a0dc(0x89);
  FUN_0800a0ce(0xff);
  FUN_0800a0dc(0x8a);
  FUN_0800a0ce(0xff);
  FUN_0800a0dc(0x8b);
  FUN_0800a0ce(0xff);
  FUN_0800a0dc(0x8c);
  FUN_0800a0ce(0xff);
  FUN_0800a0dc(0x8d);
  FUN_0800a0ce(0xff);
  FUN_0800a0dc(0x8e);
  FUN_0800a0ce(0xff);
  FUN_0800a0dc(0x8f);
  FUN_0800a0ce(0xff);
  FUN_0800a0dc(0x3a);
  FUN_0800a0ce(5);
  FUN_0800a0dc(0xec);
  FUN_0800a0ce(0x11);
  FUN_0800a0dc(0x7e);
  FUN_0800a0ce(0x7a);
  FUN_0800a0dc(0x74);
  FUN_0800a0ce(2);
  FUN_0800a0ce(0xe);
  FUN_0800a0ce(0);
  FUN_0800a0ce(0);
  FUN_0800a0ce(0x28);
  FUN_0800a0ce(0);
  FUN_0800a0ce(0);
  FUN_0800a0dc(0x98);
  FUN_0800a0ce(0x3e);
  FUN_0800a0dc(0x99);
  FUN_0800a0ce(0x3e);
  FUN_0800a0dc(0xb5);
  FUN_0800a0ce(0xe);
  FUN_0800a0ce(0xe);
  FUN_0800a0dc(0x60);
  FUN_0800a0ce(0x38);
  FUN_0800a0ce(9);
  FUN_0800a0ce(0x6d);
  FUN_0800a0ce(0x67);
  FUN_0800a0dc(99);
  FUN_0800a0ce(0x38);
  FUN_0800a0ce(0xad);
  FUN_0800a0ce(0x6d);
  FUN_0800a0ce(0x67);
  FUN_0800a0ce(5);
  FUN_0800a0dc(100);
  FUN_0800a0ce(0x38);
  FUN_0800a0ce(0xb);
  FUN_0800a0ce(0x70);
  FUN_0800a0ce(0xab);
  FUN_0800a0ce(0x6d);
  FUN_0800a0ce(0x67);
  FUN_0800a0dc(0x66);
  FUN_0800a0ce(0x38);
  FUN_0800a0ce(0xf);
  FUN_0800a0ce(0x70);
  FUN_0800a0ce(0xaf);
  FUN_0800a0ce(0x6d);
  FUN_0800a0ce(0x67);
  FUN_0800a0dc(0x6a);
  FUN_0800a0ce(0);
  FUN_0800a0ce(0);
  FUN_0800a0dc(0x68);
  FUN_0800a0ce(0x3b);
  FUN_0800a0ce(8);
  FUN_0800a0ce(4);
  FUN_0800a0ce(0);
  FUN_0800a0ce(4);
  FUN_0800a0ce(100);
  FUN_0800a0ce(0x67);
  FUN_0800a0dc(0x6c);
  FUN_0800a0ce(0x22);
  FUN_0800a0ce(2);
  FUN_0800a0ce(0x22);
  FUN_0800a0ce(2);
  FUN_0800a0ce(0x22);
  FUN_0800a0ce(0x22);
  FUN_0800a0ce(0x50);
  FUN_0800a0dc(0x6e);
  FUN_0800a0ce(0);
  FUN_0800a0ce(0);
  FUN_0800a0ce(0);
  FUN_0800a0ce(0);
  FUN_0800a0ce(7);
  FUN_0800a0ce(1);
  FUN_0800a0ce(0x13);
  FUN_0800a0ce(0x11);
  FUN_0800a0ce(0xb);
  FUN_0800a0ce(9);
  FUN_0800a0ce(0x16);
  FUN_0800a0ce(0x15);
  FUN_0800a0ce(0x1d);
  FUN_0800a0ce(0x1e);
  FUN_0800a0ce(0);
  FUN_0800a0ce(0);
  FUN_0800a0ce(0);
  FUN_0800a0ce(0);
  FUN_0800a0ce(0x1e);
  FUN_0800a0ce(0x1d);
  FUN_0800a0ce(0x15);
  FUN_0800a0ce(0x16);
  FUN_0800a0ce(10);
  FUN_0800a0ce(0xc);
  FUN_0800a0ce(0x12);
  FUN_0800a0ce(0x14);
  FUN_0800a0ce(2);
  FUN_0800a0ce(8);
  FUN_0800a0ce(0);
  FUN_0800a0ce(0);
  FUN_0800a0ce(0);
  FUN_0800a0ce(0);
  FUN_0800a0dc(0xa9);
  FUN_0800a0ce(0x1b);
  FUN_0800a0dc(0xa8);
  FUN_0800a0ce(0x6b);
  FUN_0800a0dc(0xa8);
  FUN_0800a0ce(0x6d);
  FUN_0800a0dc(0xa7);
  FUN_0800a0ce(0x40);
  FUN_0800a0dc(0xad);
  FUN_0800a0ce(0x47);
  FUN_0800a0dc(0xaf);
  FUN_0800a0ce(0x73);
  FUN_0800a0dc(0xaf);
  FUN_0800a0ce(0x73);
  FUN_0800a0dc(0xac);
  FUN_0800a0ce(0x44);
  FUN_0800a0dc(0xa3);
  FUN_0800a0ce(0x6c);
  FUN_0800a0dc(0xcb);
  FUN_0800a0ce(0);
  FUN_0800a0dc(0xcd);
  FUN_0800a0ce(0x22);
  FUN_0800a0dc(0xc2);
  FUN_0800a0ce(0x10);
  FUN_0800a0dc(0xc5);
  FUN_0800a0ce(0);
  FUN_0800a0dc(0xc6);
  FUN_0800a0ce(0xe);
  FUN_0800a0dc(199);
  FUN_0800a0ce(0x1f);
  FUN_0800a0dc(200);
  FUN_0800a0ce(0xe);
  FUN_0800a0dc(0xbf);
  FUN_0800a0ce(0);
  FUN_0800a0dc(0xf9);
  FUN_0800a0ce(0x20);
  FUN_0800a0dc(0x9b);
  FUN_0800a0ce(0x3b);
  FUN_0800a0dc(0x93);
  FUN_0800a0ce(0x33);
  FUN_0800a0ce(0x7f);
  FUN_0800a0ce(0);
  FUN_0800a0dc(0x70);
  FUN_0800a0ce(0xe);
  FUN_0800a0ce(0xf);
  FUN_0800a0ce(3);
  FUN_0800a0ce(0xe);
  FUN_0800a0ce(0xf);
  FUN_0800a0ce(3);
  FUN_0800a0dc(0x71);
  FUN_0800a0ce(0xe);
  FUN_0800a0ce(0x16);
  FUN_0800a0ce(3);
  FUN_0800a0dc(0x91);
  FUN_0800a0ce(0xe);
  FUN_0800a0ce(9);
  FUN_0800a0dc(0xc3);
  FUN_0800a0ce(0x2c);
  FUN_0800a0dc(0xc4);
  FUN_0800a0ce(0x1a);
  FUN_0800a0dc(0xf0);
  FUN_0800a0ce(0x51);
  FUN_0800a0ce(0x13);
  FUN_0800a0ce(0xc);
  FUN_0800a0ce(6);
  FUN_0800a0ce(0);
  FUN_0800a0ce(0x2f);
  FUN_0800a0dc(0xf2);
  FUN_0800a0ce(0x51);
  FUN_0800a0ce(0x13);
  FUN_0800a0ce(0xc);
  FUN_0800a0ce(6);
  FUN_0800a0ce(0);
  FUN_0800a0ce(0x33);
  FUN_0800a0dc(0xf1);
  FUN_0800a0ce(0x3c);
  FUN_0800a0ce(0x94);
  FUN_0800a0ce(0x4f);
  FUN_0800a0ce(0x33);
  FUN_0800a0ce(0x34);
  FUN_0800a0ce(0xcf);
  FUN_0800a0dc(0xf3);
  FUN_0800a0ce(0x4d);
  FUN_0800a0ce(0x94);
  FUN_0800a0ce(0x4f);
  FUN_0800a0ce(0x33);
  FUN_0800a0ce(0x34);
  FUN_0800a0ce(0xcf);
  FUN_0800a0dc(0x36);
  FUN_0800a0ce(0);
  FUN_0800a0dc(0x11);
  FUN_0800f418(200);
  FUN_0800a0dc(0x29);
  FUN_0800a0dc(0x2c);
  return;
}


/* 0800a0bc FUN_0800a0bc */

void FUN_0800a0bc(uint param_1)

{
  FUN_0800a0fc((int)param_1 >> 8);
  FUN_0800a0fc(param_1 & 0xff);
  return;
}


/* 0800a0ce FUN_0800a0ce */

void FUN_0800a0ce(undefined4 param_1)

{
  FUN_0800a0fc(param_1);
  return;
}


/* 0800a0dc FUN_0800a0dc */

void FUN_0800a0dc(undefined4 param_1)

{
  FUN_08005ffa(DAT_0800a0f8,1);
  FUN_0800a0fc(param_1);
  FUN_080098e2(DAT_0800a0f8,1);
  return;
}


/* 0800a0fc FUN_0800a0fc */

void FUN_0800a0fc(undefined4 param_1)

{
  int iVar1;
  
  FUN_08005ffa(DAT_0800a13c,0x400);
  do {
    iVar1 = FUN_0800a4b0(DAT_0800a140,2);
  } while (iVar1 == 0);
  FUN_0800a4c2(DAT_0800a140,param_1);
  do {
    iVar1 = FUN_0800a4b0(DAT_0800a140,0x80);
  } while (iVar1 == 1);
  FUN_080098e2(DAT_0800a13c,0x400);
  return;
}


/* 0800a144 FUN_0800a144 */

void FUN_0800a144(undefined4 param_1)

{
  FUN_08010a6c(0x12,param_1);
  return;
}


/* 0800a152 FUN_0800a152 */

void FUN_0800a152(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_08010a0e(0x12,param_1,param_2,param_3);
  return;
}


/* 0800a168 FUN_0800a168 */

void FUN_0800a168(undefined4 param_1,undefined4 param_2)

{
  FUN_08010ab2(0x12,param_1,param_2);
  return;
}


/* 0800a17a thunk_FUN_0800a17c */

void thunk_FUN_0800a17c(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}


/* 0800a17c FUN_0800a17c */

void FUN_0800a17c(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}


/* 0800a180 FUN_0800a180 */

void FUN_0800a180(byte *param_1)

{
  uint uVar1;
  
  if (param_1[3] == 0) {
    *(int *)(DAT_0800a1ec + ((int)(uint)*param_1 >> 5) * 4) = 1 << (*param_1 & 0x1f);
  }
  else {
    uVar1 = 0x700 - (*DAT_0800a1e4 & 0x700) >> 8;
    *(char *)(DAT_0800a1e8 + (uint)*param_1) =
         (char)(((uint)param_1[1] << (4 - uVar1 & 0xff) | (uint)param_1[2] & 0xfU >> (uVar1 & 0xff))
               << 4);
    *(int *)(((int)(uint)*param_1 >> 5) * 4 + -0x1fff1f00) = 1 << (*param_1 & 0x1f);
  }
  return;
}


/* 0800a1f0 FUN_0800a1f0 */

void FUN_0800a1f0(uint param_1)

{
  *DAT_0800a200 = DAT_0800a1fc | param_1;
  return;
}


/* 0800a204 FUN_0800a204 */

void FUN_0800a204(uint param_1,uint param_2)

{
  *DAT_0800a214 = DAT_0800a210 & param_2 | param_1;
  return;
}


/* 0800a218 FUN_0800a218 */

void FUN_0800a218(uint param_1)

{
  *(uint *)(DAT_0800a22c + 0x2c) = *(uint *)(DAT_0800a22c + 0x2c) & 0xfffffff0 | param_1;
  return;
}


/* 0800a230 FUN_0800a230 */

void FUN_0800a230(uint param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = *(uint *)(DAT_0800a250 + 0x2c) & 0xfffffe0f;
  if (param_2 == 0) {
    uVar1 = uVar1 | param_1 & 0xfffffeff;
  }
  else {
    uVar1 = uVar1 | param_1;
  }
  *(uint *)(DAT_0800a250 + 0x2c) = uVar1;
  return;
}


/* 0800a254 FUN_0800a254 */

void FUN_0800a254(uint param_1,int param_2)

{
  if (param_2 == 0) {
    *(uint *)(DAT_0800a270 + 0x14) = *(uint *)(DAT_0800a270 + 0x14) & ~param_1;
  }
  else {
    *(uint *)(DAT_0800a270 + 0x14) = *(uint *)(DAT_0800a270 + 0x14) | param_1;
  }
  return;
}


/* 0800a274 FUN_0800a274 */

void FUN_0800a274(uint param_1,int param_2)

{
  if (param_2 == 0) {
    *(uint *)(DAT_0800a290 + 0x28) = *(uint *)(DAT_0800a290 + 0x28) & ~param_1;
  }
  else {
    *(uint *)(DAT_0800a290 + 0x28) = *(uint *)(DAT_0800a290 + 0x28) | param_1;
  }
  return;
}


/* 0800a294 FUN_0800a294 */

void FUN_0800a294(uint param_1,int param_2)

{
  if (param_2 == 0) {
    *(uint *)(DAT_0800a2b0 + 0x1c) = *(uint *)(DAT_0800a2b0 + 0x1c) & ~param_1;
  }
  else {
    *(uint *)(DAT_0800a2b0 + 0x1c) = *(uint *)(DAT_0800a2b0 + 0x1c) | param_1;
  }
  return;
}


/* 0800a2b4 FUN_0800a2b4 */

void FUN_0800a2b4(uint param_1,int param_2)

{
  if (param_2 == 0) {
    *(uint *)(DAT_0800a2d0 + 0x18) = *(uint *)(DAT_0800a2d0 + 0x18) & ~param_1;
  }
  else {
    *(uint *)(DAT_0800a2d0 + 0x18) = *(uint *)(DAT_0800a2d0 + 0x18) | param_1;
  }
  return;
}


/* 0800a2d4 FUN_0800a2d4 */

void FUN_0800a2d4(undefined4 param_1)

{
  *DAT_0800a2dc = param_1;
  return;
}


/* 0800a2e0 FUN_0800a2e0 */

void FUN_0800a2e0(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  
  uVar2 = *(uint *)(DAT_0800a410 + 4) & DAT_0800a414;
  uVar4 = (uint)(*(int *)(DAT_0800a410 + 0x24) << 0x19) >> 0x1d;
  if ((uVar2 & 0x8000000) == 0) {
    iVar3 = (uVar2 >> 0x12) + 2;
  }
  else {
    iVar3 = (uVar2 >> 0x12) - 0x1ef;
  }
  if ((*(uint *)(DAT_0800a410 + 4) & 0x10000) == 0) {
    if ((*(uint *)(DAT_0800a410 + 0x40) & 1) == 0) {
      uVar2 = iVar3 * DAT_0800a41c;
    }
    else {
      uVar2 = iVar3 * DAT_0800a418;
    }
  }
  else if ((*(uint *)(DAT_0800a410 + 4) & 0x20000) == 0) {
    uVar2 = iVar3 * DAT_0800a424;
  }
  else {
    uVar2 = iVar3 * DAT_0800a420;
  }
  if ((*(uint *)(DAT_0800a410 + 0x40) & 2) != 0) {
    uVar2 = uVar2 >> 1;
  }
  uVar1 = *(uint *)(DAT_0800a410 + 4) & 0xc;
  if (uVar1 == 0) {
    *param_1 = *(uint *)(DAT_0800a428 + uVar4 * 4);
  }
  else if (uVar1 == 4) {
    *param_1 = DAT_0800a41c;
  }
  else if (uVar1 == 8) {
    *param_1 = DAT_0800a424;
  }
  else if (uVar1 == 0xc) {
    *param_1 = uVar2;
  }
  else {
    *param_1 = *(uint *)(DAT_0800a428 + uVar4 * 4);
  }
  param_1[1] = *param_1 >> *(sbyte *)(DAT_0800a42c + ((*(uint *)(DAT_0800a410 + 4) & 0xf0) >> 4));
  param_1[2] = param_1[1] >> *(sbyte *)(DAT_0800a42c + ((*(uint *)(DAT_0800a410 + 4) & 0x700) >> 8))
  ;
  param_1[3] = param_1[1] >>
               *(sbyte *)(DAT_0800a42c + ((*(uint *)(DAT_0800a410 + 4) & 0x3800) >> 0xb));
  param_1[5] = param_1[1] / (uint)*(byte *)(DAT_0800a430 + (*(uint *)(DAT_0800a410 + 0x2c) & 0xf));
  param_1[4] = uVar2 / *(ushort *)
                        (DAT_0800a434 + ((*(uint *)(DAT_0800a410 + 0x2c) & 0x1f0) >> 4 & 0xf) * 2);
  return;
}


/* 0800a438 FUN_0800a438 */

bool FUN_0800a438(uint param_1)

{
  uint uVar1;
  
  if ((int)param_1 >> 5 == 1) {
    uVar1 = *DAT_0800a470;
  }
  else if ((int)param_1 >> 5 == 2) {
    uVar1 = DAT_0800a470[8];
  }
  else {
    uVar1 = DAT_0800a470[9];
  }
  return (1 << (param_1 & 0x1f) & uVar1) != 0;
}


/* 0800a474 FUN_0800a474 */

void FUN_0800a474(ushort *param_1,ushort param_2)

{
  *param_1 = *param_1 & 0xf7ff;
  *param_1 = *param_1 | param_2;
  return;
}


/* 0800a486 FUN_0800a486 */

void FUN_0800a486(ushort *param_1,int param_2)

{
  if (param_2 == 0) {
    *param_1 = *param_1 & 0xffbf;
  }
  else {
    *param_1 = *param_1 | 0x40;
  }
  return;
}


/* 0800a49e FUN_0800a49e */

void FUN_0800a49e(int param_1,ushort param_2,int param_3)

{
  if (param_3 == 0) {
    *(ushort *)(param_1 + 4) = *(ushort *)(param_1 + 4) & ~param_2;
  }
  else {
    *(ushort *)(param_1 + 4) = *(ushort *)(param_1 + 4) | param_2;
  }
  return;
}


/* 0800a4b0 FUN_0800a4b0 */

bool FUN_0800a4b0(int param_1,ushort param_2)

{
  return (*(ushort *)(param_1 + 8) & param_2) != 0;
}


/* 0800a4c2 FUN_0800a4c2 */

void FUN_0800a4c2(int param_1,undefined2 param_2)

{
  *(undefined2 *)(param_1 + 0xc) = param_2;
  return;
}


/* 0800a4c6 FUN_0800a4c6 */

void FUN_0800a4c6(ushort *param_1,ushort *param_2)

{
  *param_1 = *param_1 & 0x3040 |
             *param_2 | param_2[1] | param_2[2] | param_2[3] | param_2[4] | param_2[5] | param_2[6]
             | param_2[7];
  param_1[0xe] = param_1[0xe] & 0xf7ff;
  param_1[8] = param_2[8];
  return;
}


/* 0800a502 FUN_0800a502 */

void FUN_0800a502(void)

{
  return;
}


/* 0800a504 FUN_0800a504 */

void FUN_0800a504(void)

{
  uint *puVar1;
  uint *puVar2;
  int iVar3;
  
  iVar3 = 0;
  *DAT_0800a5e4 = *DAT_0800a5e4 | 0x10000;
  do {
    iVar3 = iVar3 + 1;
    if ((int)(*DAT_0800a5e4 << 0xe) < 0) break;
  } while (iVar3 != 0x2000);
  if ((int)(*DAT_0800a5e4 << 0xe) < 0) {
    FUN_08005f88();
    puVar1 = DAT_0800a5f0;
    *DAT_0800a5f0 = *DAT_0800a5f0 & 0xfffffffc;
    *puVar1 = *puVar1 | 1;
    puVar1 = DAT_0800a5e4;
    DAT_0800a5e4[1] = DAT_0800a5e4[1];
    puVar1[1] = puVar1[1] | 0x2000;
    puVar1[1] = puVar1[1] | 0x500;
    puVar2 = DAT_0800a5e4;
    DAT_0800a5e4[1] = puVar1[1] & DAT_0800a5f4;
    puVar2[0x10] = puVar2[0x10] & 0xfffffffc;
    puVar2[1] = puVar2[1] | 0x230000;
    puVar2[0x10] = puVar2[0x10];
    *puVar2 = *puVar2 | 0x1000000;
    puVar1 = DAT_0800a5e4;
    do {
    } while ((*DAT_0800a5e4 & 0x2000000) == 0);
    DAT_0800a5e4[1] = DAT_0800a5e4[1] & 0xfffffffc;
    puVar1[1] = puVar1[1] | 3;
    do {
    } while ((DAT_0800a5e4[1] & 0xc) != 0xc);
  }
  else {
    *DAT_0800a5ec = DAT_0800a5e8;
  }
  return;
}


/* 0800a5f8 FUN_0800a5f8 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0800a5f8(int param_1)

{
  if (param_1 == 4) {
    _DAT_e000e010 = _DAT_e000e010 | 4;
  }
  else {
    _DAT_e000e010 = _DAT_e000e010 & 0xfffffffb;
  }
  return;
}


/* 0800a620 FUN_0800a620 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0800a620(void)

{
  *DAT_0800a63c = *DAT_0800a63c + 1;
  *DAT_0800a640 = _DAT_e000e018;
  *DAT_0800a644 = 0;
  return;
}


/* 0800a648 FUN_0800a648 */

void FUN_0800a648(void)

{
  uint *puVar1;
  uint *puVar2;
  
  *DAT_0800a708 = *DAT_0800a708 | 0xf00000;
  puVar1 = DAT_0800a70c;
  DAT_0800a70c[9] = DAT_0800a70c[9] | 4;
  puVar2 = DAT_0800a70c;
  DAT_0800a70c[1] = puVar1[1] & DAT_0800a710;
  puVar1 = DAT_0800a70c;
  *DAT_0800a70c = *puVar2 & DAT_0800a714;
  *puVar1 = *puVar1 & 0xfffbffff;
  puVar2 = DAT_0800a70c;
  DAT_0800a70c[1] = puVar1[1] & DAT_0800a718;
  puVar2[0xb] = 0x7000;
  puVar2[0xc] = 0x3800;
  puVar2[0xd] = 0;
  puVar2[0x10] = 0;
  puVar2[2] = DAT_0800a71c;
  puVar2[7] = puVar2[7] | 0x10000000;
  puVar1 = DAT_0800a724;
  if ((*DAT_0800a720 & 0x400) == 0x400) {
    *DAT_0800a724 = *DAT_0800a724 & 0xfdffffff;
    *puVar1 = *puVar1 | 0x2000000;
  }
  puVar1 = DAT_0800a728;
  *DAT_0800a728 = *DAT_0800a728 | 0x90;
  if ((*puVar1 & 0x100) != 0) {
    *puVar1 = *puVar1 & 0xfffffdff;
  }
  FUN_0800a504();
  DAT_0800a708[-0x20] = 0x8000000;
  return;
}


/* 0800a72c FUN_0800a72c */

void FUN_0800a72c(void)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  
  iVar3 = FUN_0800a880(DAT_0800a7b4,1);
  pcVar1 = DAT_0800a7b8;
  if (iVar3 == 1) {
    *DAT_0800a7b8 = *DAT_0800a7b8 == '\0';
    if ((*pcVar1 != '\0') &&
       (pcVar1[1] = pcVar1[1] + '\x01', pcVar2 = DAT_0800a7b8,
       (uint)(byte)pcVar1[1] == ((byte)pcVar1[1] / 0x3c) * 0x3c)) {
      DAT_0800a7b8[1] = '\0';
      pcVar2[2] = pcVar2[2] + '\x01';
      pcVar1 = DAT_0800a7b8;
      if ((uint)(byte)pcVar2[2] == ((byte)pcVar2[2] / 0x3c) * 0x3c) {
        DAT_0800a7b8[2] = '\0';
        pcVar1[3] = pcVar1[3] + '\x01';
        if ((uint)(byte)pcVar1[3] == ((byte)pcVar1[3] / 0x18) * 0x18) {
          DAT_0800a7b8[3] = '\0';
        }
      }
    }
    FUN_0800a7e8(DAT_0800a7b4,1);
  }
  return;
}


/* 0800a7bc FUN_0800a7bc */

void FUN_0800a7bc(void)

{
  int iVar1;
  
  iVar1 = FUN_0800a880(DAT_0800a7e0,1);
  if ((iVar1 == 1) && (FUN_0800a7e8(DAT_0800a7e0,1), *DAT_0800a7e4 != 0)) {
    (*(code *)*DAT_0800a7e4)();
  }
  return;
}


/* 0800a7e8 FUN_0800a7e8 */

void FUN_0800a7e8(int param_1,uint param_2)

{
  *(uint *)(param_1 + 0x10) = ~param_2;
  return;
}


/* 0800a7ee FUN_0800a7ee */

void FUN_0800a7ee(uint *param_1,int param_2)

{
  if (param_2 == 0) {
    *param_1 = *param_1 & 0xffffff7f;
  }
  else {
    *param_1 = *param_1 | 0x80;
  }
  return;
}


/* 0800a804 FUN_0800a804 */

void FUN_0800a804(int param_1,ushort param_2)

{
  *(ushort *)(param_1 + 0x18) = *(ushort *)(param_1 + 0x18) & 0xff8f | param_2;
  return;
}


/* 0800a816 FUN_0800a816 */

void FUN_0800a816(int param_1,ushort param_2,int param_3)

{
  if (param_3 == 0) {
    *(ushort *)(param_1 + 0xc) = *(ushort *)(param_1 + 0xc) & ~param_2;
  }
  else {
    *(ushort *)(param_1 + 0xc) = *(ushort *)(param_1 + 0xc) | param_2;
  }
  return;
}


/* 0800a828 FUN_0800a828 */

void FUN_0800a828(int param_1,ushort param_2)

{
  *(ushort *)(param_1 + 0x18) = *(ushort *)(param_1 + 0x18) & 0xfffb | param_2;
  return;
}


/* 0800a83a FUN_0800a83a */

void FUN_0800a83a(int param_1,ushort param_2)

{
  *(ushort *)(param_1 + 0x18) = *(ushort *)(param_1 + 0x18) & 0xfff7 | param_2;
  return;
}


/* 0800a84c FUN_0800a84c */

void FUN_0800a84c(uint *param_1,int param_2)

{
  if (param_2 == 0) {
    *param_1 = *param_1 & 0xfffffffe;
  }
  else {
    *param_1 = *param_1 | 1;
  }
  return;
}


/* 0800a862 FUN_0800a862 */

void FUN_0800a862(int param_1,int param_2)

{
  if (param_2 == 0) {
    *(ushort *)(param_1 + 0x44) = (ushort)(((uint)*(ushort *)(param_1 + 0x44) << 0x11) >> 0x11);
  }
  else {
    *(ushort *)(param_1 + 0x44) = *(ushort *)(param_1 + 0x44) | 0x8000;
  }
  return;
}


/* 0800a880 FUN_0800a880 */

undefined4 FUN_0800a880(int param_1,uint param_2)

{
  undefined4 uVar1;
  
  if (((*(uint *)(param_1 + 0x10) & param_2) == 0) || ((*(ushort *)(param_1 + 0xc) & param_2) == 0))
  {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}


/* 0800a8a4 FUN_0800a8a4 */

void FUN_0800a8a4(int param_1,ushort *param_2)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  
  *(uint *)(param_1 + 0x20) = *(uint *)(param_1 + 0x20) & 0xfffffffe;
  uVar3 = *(uint *)(param_1 + 4);
  uVar1 = *param_2;
  uVar2 = *(uint *)(param_1 + 0x20) & 0xfffffffd | (uint)param_2[4] | (uint)param_2[1];
  if ((param_1 == DAT_0800a910) || (param_1 == DAT_0800a914)) {
    uVar2 = (uVar2 & 0xfffffff7 | (uint)param_2[5]) & 0xfffffffb | (uint)param_2[2];
    uVar3 = uVar3 & 0xfffffcff | (uint)param_2[6] | (uint)param_2[7];
  }
  *(uint *)(param_1 + 4) = uVar3;
  *(ushort *)(param_1 + 0x18) = *(ushort *)(param_1 + 0x18) & 0xff8c | uVar1;
  *(ushort *)(param_1 + 0x34) = param_2[3];
  *(uint *)(param_1 + 0x20) = uVar2;
  return;
}


/* 0800a918 FUN_0800a918 */

void FUN_0800a918(undefined2 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  return;
}


/* 0800a92c FUN_0800a92c */

void FUN_0800a92c(undefined2 *param_1)

{
  param_1[2] = 0xffff;
  *param_1 = 0;
  param_1[3] = 0;
  param_1[1] = 0;
  *(undefined1 *)(param_1 + 4) = 0;
  *(undefined1 *)((int)param_1 + 9) = 0;
  *(undefined1 *)(param_1 + 5) = 0;
  *(undefined1 *)((int)param_1 + 0xb) = 0;
  *(undefined1 *)(param_1 + 6) = 0;
  *(undefined1 *)((int)param_1 + 0xd) = 0;
  *(undefined1 *)(param_1 + 7) = 0;
  return;
}


/* 0800a94c FUN_0800a94c */

void FUN_0800a94c(uint *param_1,undefined2 *param_2)

{
  uint uVar1;
  
  uVar1 = *param_1;
  if ((((param_1 == DAT_0800aa74) || (param_1 == DAT_0800aa78)) || (param_1 == (uint *)0x40000000))
     || (((param_1 == DAT_0800aa7c || (param_1 == DAT_0800aa80)) ||
         ((param_1 == DAT_0800aa84 || (param_1 == DAT_0800aa88)))))) {
    uVar1 = uVar1 & 0xffffff8f | (uint)(ushort)param_2[1];
  }
  if ((param_1 != DAT_0800aa8c) && (param_1 != DAT_0800aa90)) {
    uVar1 = uVar1 & 0xfffffcff | (uint)(ushort)param_2[3];
  }
  *param_1 = uVar1;
  *(undefined2 *)(param_1 + 0xb) = param_2[2];
  *(undefined2 *)(param_1 + 10) = *param_2;
  if ((param_1 == DAT_0800aa74) || (param_1 == DAT_0800aa78)) {
    *(ushort *)(param_1 + 0xc) = (ushort)*(byte *)(param_2 + 4);
  }
  *(undefined2 *)(param_1 + 5) = 1;
  uVar1 = *param_1;
  if (((((param_1 == DAT_0800aa74) || (param_1 == DAT_0800aa78)) || (param_1 == (uint *)0x40000000))
      || ((param_1 == DAT_0800aa7c || (param_1 == DAT_0800aa80)))) ||
     ((param_1 == DAT_0800aa84 || (param_1 == DAT_0800aa88)))) {
    if (*(char *)((int)param_2 + 9) == '\0') {
      uVar1 = uVar1 & 0xfffff7ff;
    }
    else {
      uVar1 = uVar1 | 0x800;
    }
  }
  if (param_1 == DAT_0800aa88) {
    if (*(char *)(param_2 + 5) == '\0') {
      uVar1 = uVar1 & 0xffffefff;
    }
    else {
      uVar1 = uVar1 | 0x1000;
    }
    if (*(char *)((int)param_2 + 0xb) == '\0') {
      uVar1 = uVar1 & 0xffffdfff;
    }
    else {
      uVar1 = uVar1 | 0x2000;
    }
    if (*(char *)(param_2 + 6) == '\0') {
      uVar1 = uVar1 & 0xffffbfff;
    }
    else {
      uVar1 = uVar1 | 0x4000;
    }
  }
  if (((param_1 == DAT_0800aa74) || (param_1 == DAT_0800aa78)) ||
     ((param_1 == (uint *)0x40000000 ||
      (((param_1 == DAT_0800aa7c || (param_1 == DAT_0800aa80)) || (param_1 == DAT_0800aa88)))))) {
    if (*(char *)((int)param_2 + 0xd) == '\0') {
      uVar1 = uVar1 & 0xffff7fff;
    }
    else {
      uVar1 = uVar1 | 0x8000;
    }
  }
  *param_1 = uVar1;
  uVar1 = param_1[1];
  if ((param_1 == (uint *)0x40000000) || (param_1 == DAT_0800aa80)) {
    if (*(char *)(param_2 + 7) == '\0') {
      uVar1 = uVar1 & 0xfffffeff;
    }
    else {
      uVar1 = uVar1 | 0x100;
    }
  }
  param_1[1] = uVar1;
  return;
}


/* 0800aa94 FUN_0800aa94 */

void FUN_0800aa94(void)

{
  int iVar1;
  
  FUN_0800aacc(DAT_0800aab0,0x20);
  iVar1 = FUN_0800aacc(DAT_0800aab0,8);
  if (iVar1 != 0) {
    FUN_0800ab9c(DAT_0800aab0);
  }
  return;
}


/* 0800aab4 FUN_0800aab4 */

void FUN_0800aab4(int param_1,int param_2)

{
  if (param_2 == 0) {
    *(ushort *)(param_1 + 0xc) = *(ushort *)(param_1 + 0xc) & 0xdfff;
  }
  else {
    *(ushort *)(param_1 + 0xc) = *(ushort *)(param_1 + 0xc) | 0x2000;
  }
  return;
}


/* 0800aacc FUN_0800aacc */

bool FUN_0800aacc(ushort *param_1,ushort param_2)

{
  return (*param_1 & param_2) != 0;
}


/* 0800aae8 FUN_0800aae8 */

void FUN_0800aae8(int param_1,int *param_2)

{
  uint uVar1;
  undefined1 auStack_38 [8];
  int local_30;
  int local_2c;
  
  *(ushort *)(param_1 + 0x10) = *(ushort *)(param_1 + 0x10) & 0xcfff | *(ushort *)((int)param_2 + 6)
  ;
  *(ushort *)(param_1 + 0xc) =
       *(ushort *)(param_1 + 0xc) & 0xe9f3 |
       *(ushort *)(param_2 + 1) | *(ushort *)(param_2 + 2) | *(ushort *)((int)param_2 + 10);
  *(ushort *)(param_1 + 0x14) = *(ushort *)(param_1 + 0x14) & 0xfcff | *(ushort *)(param_2 + 3);
  FUN_0800a2e0(auStack_38);
  if (((param_1 != DAT_0800ab90) && (param_1 != DAT_0800ab94)) && (param_1 != DAT_0800ab98)) {
    local_2c = local_30;
  }
  uVar1 = (uint)(local_2c * 0x19) / (uint)(*param_2 << 2);
  *(ushort *)(param_1 + 8) =
       (ushort)(uVar1 / 100 << 4) | (ushort)(((uVar1 % 100) * 0x10 + 0x32) / 100) & 0xf;
  return;
}


/* 0800ab9c FUN_0800ab9c */

ushort FUN_0800ab9c(int param_1)

{
  return *(ushort *)(param_1 + 4) & 0x1ff;
}


/* 0800aba6 FUN_0800aba6 */

void FUN_0800aba6(int param_1,int param_2)

{
  *(ushort *)(param_1 + 4) = (ushort)((uint)(param_2 << 0x17) >> 0x17);
  return;
}


/* 0800abae FUN_0800abae */

void FUN_0800abae(undefined4 *param_1)

{
  *param_1 = 0x2580;
  *(undefined2 *)(param_1 + 1) = 0;
  *(undefined2 *)((int)param_1 + 6) = 0;
  *(undefined2 *)(param_1 + 2) = 0;
  *(undefined2 *)((int)param_1 + 10) = 0xc;
  *(undefined2 *)(param_1 + 3) = 0;
  return;
}


/* 0800abc6 FUN_0800abc6 */

void FUN_0800abc6(void)

{
  FUN_08009518(0x20000);
  return;
}


/* 0800abd2 FUN_0800abd2 */

void FUN_0800abd2(void)

{
  return;
}


/* 0800abd4 thunk_FUN_0800abd6 */

void thunk_FUN_0800abd6(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}


/* 0800abd6 FUN_0800abd6 */

void FUN_0800abd6(void)

{
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}


/* 0800abd8 FUN_0800abd8 */

undefined4 FUN_0800abd8(undefined4 param_1,float param_2,float param_3)

{
  undefined4 uVar1;
  undefined1 in_ZR;
  char in_CY;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  
  uVar2 = FUN_08005854(param_3);
  uVar3 = FUN_08005854(param_1);
  uVar3 = FUN_0800b4e8((int)uVar3,(int)((ulonglong)uVar3 >> 0x20));
  FUN_0800587c((int)uVar3,(int)((ulonglong)uVar3 >> 0x20),(int)uVar2,(int)((ulonglong)uVar2 >> 0x20)
              );
  if ((bool)in_CY && !(bool)in_ZR) {
    uVar2 = FUN_08005854(param_2);
    uVar3 = FUN_08005854(param_1);
    uVar3 = FUN_0800b4e8((int)uVar3,(int)((ulonglong)uVar3 >> 0x20));
    FUN_080058ac((int)uVar3,(int)((ulonglong)uVar3 >> 0x20),(int)uVar2,
                 (int)((ulonglong)uVar2 >> 0x20));
    uVar1 = DAT_0800ace4;
    if (in_CY != '\0') {
      uVar2 = FUN_08005854(param_2 - param_3);
      uVar3 = FUN_08005854(param_1);
      uVar3 = FUN_0800b4e8((int)uVar3,(int)((ulonglong)uVar3 >> 0x20));
      uVar4 = FUN_08005854(param_2);
      uVar3 = FUN_0800560c((int)uVar4,(int)((ulonglong)uVar4 >> 0x20),(int)uVar3,
                           (int)((ulonglong)uVar3 >> 0x20));
      FUN_080056fc((int)uVar3,(int)((ulonglong)uVar3 >> 0x20),(int)uVar2,
                   (int)((ulonglong)uVar2 >> 0x20));
      uVar1 = FUN_080058dc();
    }
  }
  else {
    uVar1 = 0x3f800000;
  }
  return uVar1;
}


/* 0800ace8 FUN_0800ace8 */

void FUN_0800ace8(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  uStack_c = param_2;
  uStack_8 = param_3;
  uStack_4 = param_4;
  FUN_0800d5c0(param_1,&uStack_c,DAT_0800ad04,DAT_0800ad00);
  return;
}


/* 0800ad08 FUN_0800ad08 */

undefined4 FUN_0800ad08(undefined1 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined1 *local_20;
  int iStack_1c;
  undefined4 uStack_4;
  
  uVar1 = 0;
  if (param_2 != 0) {
    iStack_1c = param_2 + -1;
    local_20 = param_1;
    uStack_4 = param_4;
    uVar1 = FUN_0800d5c0(param_3,&uStack_4,&local_20,DAT_0800ad34);
    *local_20 = 0;
  }
  return uVar1;
}


/* 0800ad38 FUN_0800ad38 */

undefined4 FUN_0800ad38(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uStack_10;
  undefined4 local_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  uStack_10 = param_1;
  local_c = param_2;
  uStack_8 = param_3;
  uStack_4 = param_4;
  uVar1 = FUN_0800d5c0(param_2,&uStack_8,&uStack_10,DAT_0800ad5c);
  FUN_0800dd4a(0,&uStack_10);
  return uVar1;
}


/* 0800ad60 FUN_0800ad60 */

undefined4 FUN_0800ad60(undefined1 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined1 *local_18;
  int iStack_14;
  
  uVar1 = 0;
  if (param_2 != 0) {
    iStack_14 = param_2 + -1;
    local_18 = param_1;
    uVar1 = FUN_0800d5c0(param_3,param_4,&local_18,DAT_0800ad88);
    *local_18 = 0;
  }
  return uVar1;
}


/* 0800ad8c FUN_0800ad8c */

uint FUN_0800ad8c(uint param_1,int param_2)

{
  param_1 = param_1 | param_2 << 0xc;
  if (param_1 != 0) {
    param_1 = 4;
  }
  if ((uint)(param_2 << 1) >> 0x15 != 0) {
    param_1 = param_1 | 1;
  }
  if ((uint)(param_2 << 1) >> 0x15 == 0x7ff) {
    param_1 = param_1 | 2;
  }
  if (param_1 == 1) {
    param_1 = 5;
  }
  return param_1;
}


/* 0800adbc FUN_0800adbc */

void FUN_0800adbc(uint param_1,int param_2)

{
  if ((int)param_1 < 0) {
    *(char *)(DAT_0800ade0 + ((param_1 & 0xf) - 4)) = (char)((uint)(param_2 << 0x1c) >> 0x18);
  }
  else {
    *(char *)(DAT_0800addc + param_1) = (char)((uint)(param_2 << 0x1c) >> 0x18);
  }
  return;
}


/* 0800ade4 FUN_0800ade4 */

void FUN_0800ade4(undefined4 param_1)

{
  *(undefined4 *)(*DAT_0800adec + 0x30) = param_1;
  return;
}


/* 0800adf0 FUN_0800adf0 */

void FUN_0800adf0(void)

{
  FUN_0800f7b8();
  FUN_0800fdc4(0,0xff);
  FUN_0800fdc4(1,0x83);
  FUN_0800fdc4(2,0x83);
  FUN_0800fdc4(3,0x83);
  FUN_0800fdc4(4,0x83);
  FUN_0800fdc4(5,3);
  FUN_0800ff64();
  return;
}


/* 0800ae2c FUN_0800ae2c */

void FUN_0800ae2c(void)

{
  int iVar1;
  
  FUN_0800cc64(DAT_0800ae78,0);
  FUN_0800ccec(DAT_0800ae78);
  if ((*(byte *)(DAT_0800ae7c + 0x1c) & 0x7f) == 0) {
    if ((*(char *)(*DAT_0800ae80 + 0x50) == '\x01') &&
       ((iVar1 = FUN_08013a68(), iVar1 == 0 || (iVar1 = FUN_08013a68(), iVar1 == 0xd)))) {
      FUN_08014cd4(0xd);
    }
    else {
      FUN_08014cd4(1);
    }
  }
  else {
    FUN_08014cd4(9);
  }
  return;
}


/* 0800ae84 FUN_0800ae84 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0800ae84(void)

{
  if (((*(char *)(*DAT_0800aed4 + 0x2a) == '\x01') && (*(int *)(*_DAT_0800aed8 + 0x10) == 0)) &&
     (*(int *)(*DAT_0800aed4 + 0x30) == 0)) {
    FUN_0800f200(3);
    FUN_0800f808(3,s_ctrl_task_0800af0c,s____src_app_src_ctrl_task_c_0800aef0,DAT_0800aeec,0x28b,
                 s_T12_STA_SLEEP_0800aedb + 1);
    FUN_0800f270(*(undefined4 *)(*_DAT_0800aed8 + 0xc));
    FUN_0800ade4(*(undefined4 *)(*_DAT_0800aed8 + 0x14));
  }
  return;
}


/* 0800af18 FUN_0800af18 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0800af18(void)

{
  if ((*(char *)(*_DAT_0800af78 + 0x2a) == '\x03') || (*(char *)(*_DAT_0800af78 + 0x2a) == '\x04'))
  {
    if ((*(char *)(*_DAT_0800af78 + 0x2a) != '\x05') || (0 < *(int *)(*_DAT_0800af78 + 0x2c))) {
      FUN_0800e27c(4);
    }
    FUN_0800f200(1);
    FUN_0800f808(3,s_ctrl_task_0800afac,s____src_app_src_ctrl_task_c_0800af90,DAT_0800af8c,0x29b,
                 s_T12_STA_WORK_0800af7b + 1);
    FUN_0800f270(*(undefined4 *)(*DAT_0800afb8 + 4));
  }
  return;
}


/* 0800afbc FUN_0800afbc */

void FUN_0800afbc(void)

{
  int iVar1;
  
  iVar1 = FUN_08009534();
  if (iVar1 == 1) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  return;
}


/* 0800afcc FUN_0800afcc */

void FUN_0800afcc(int param_1)

{
  int local_28 [6];
  undefined4 local_10;
  
  if (param_1 == 0) {
    local_28[0] = *(int *)(DAT_0800b018 + (uint)*(byte *)(*DAT_0800b014 + 4) * 0x40 + 0x34) + 3;
    local_28[1] = 0xffffffce;
    local_28[2] = 0x32;
    local_28[3] = 1;
    local_28[4] = *DAT_0800b01c + 0x24;
    local_10 = 0;
    FUN_08015594(local_28);
    FUN_08014cd4(6);
  }
  return;
}


/* 0800b020 FUN_0800b020 */

void FUN_0800b020(int param_1)

{
  if (param_1 == 0) {
    FUN_08014cd4(7);
  }
  return;
}


/* 0800b030 FUN_0800b030 */

void FUN_0800b030(void)

{
  if (*(int *)(*DAT_0800b054 + 0x10) == 0) {
    FUN_0800ae2c();
  }
  else {
    FUN_0800ccec(*(undefined4 *)(*DAT_0800b054 + 0x10));
    *DAT_0800b058 = 0;
  }
  return;
}


/* 0800b05c FUN_0800b05c */

void FUN_0800b05c(void)

{
  if (*(int *)(*DAT_0800b078 + 0x14) != 0) {
    FUN_0800ccec(*(undefined4 *)(*DAT_0800b078 + 0x14));
    *DAT_0800b07c = 0;
  }
  return;
}


/* 0800b080 FUN_0800b080 */

void FUN_0800b080(int param_1)

{
  if (param_1 == 0) {
    FUN_08014cd4(0xe);
  }
  return;
}


/* 0800b090 FUN_0800b090 */

void FUN_0800b090(int param_1)

{
  int local_28 [6];
  undefined4 local_10;
  
  if (param_1 == 0) {
    local_28[0] = *(int *)(DAT_0800b0dc + (uint)*(byte *)(*DAT_0800b0d8 + 4) * 0x40 + 0x18) + 2;
    local_28[1] = 0;
    local_28[2] = 0x4b0;
    local_28[3] = 10;
    local_28[4] = *DAT_0800b0e0 + 0x14;
    local_10 = 0;
    FUN_08015594(local_28);
    FUN_08014cd4(6);
  }
  return;
}


/* 0800b0e4 FUN_0800b0e4 */

void FUN_0800b0e4(int param_1)

{
  int local_28 [6];
  undefined4 local_10;
  
  if (param_1 == 0) {
    local_28[0] = *(int *)(DAT_0800b130 + (uint)*(byte *)(*DAT_0800b12c + 4) * 0x40 + 0x10) + 2;
    local_28[1] = 0x50;
    local_28[2] = 300;
    local_28[3] = 10;
    local_28[4] = *DAT_0800b134 + 0xc;
    local_10 = 0;
    FUN_08015594(local_28);
    FUN_08014cd4(6);
  }
  return;
}


/* 0800b138 FUN_0800b138 */

void FUN_0800b138(int param_1)

{
  int local_28 [6];
  undefined4 local_10;
  
  if (param_1 == 0) {
    local_28[0] = *(int *)(DAT_0800b184 + (uint)*(byte *)(*DAT_0800b180 + 4) * 0x40 + 0x14) + 2;
    local_28[1] = 0;
    local_28[2] = 0x4b0;
    local_28[3] = 10;
    local_28[4] = *DAT_0800b188 + 0x10;
    local_10 = 0;
    FUN_08015594(local_28);
    FUN_08014cd4(6);
  }
  return;
}


/* 0800b18c FUN_0800b18c */

void FUN_0800b18c(int param_1)

{
  if (param_1 == 0) {
    FUN_08014cd4(0xf);
  }
  return;
}


/* 0800b19c FUN_0800b19c */

void FUN_0800b19c(int param_1)

{
  int local_28 [6];
  undefined4 local_10;
  
  if (param_1 == 0) {
    local_28[0] = *(int *)(DAT_0800b1e8 + (uint)*(byte *)(*DAT_0800b1e4 + 4) * 0x40 + 8) + 2;
    local_28[1] = 5;
    local_28[2] = 0x32;
    local_28[3] = 1;
    local_28[4] = *DAT_0800b1ec + 8;
    local_10 = 0;
    FUN_08015594(local_28);
    FUN_08014cd4(6);
  }
  return;
}


/* 0800b1f0 FUN_0800b1f0 */

void FUN_0800b1f0(int param_1)

{
  if (param_1 == 0) {
    FUN_08014cd4(8);
  }
  return;
}


/* 0800b200 FUN_0800b200 */

void FUN_0800b200(int param_1)

{
  if (param_1 == 0) {
    FUN_08014cd4(5);
  }
  return;
}


/* 0800b210 FUN_0800b210 */

int FUN_0800b210(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  longlong in_d0;
  undefined4 extraout_s1;
  undefined4 extraout_s1_00;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 local_18;
  
  local_18._4_4_ = (uint)((ulonglong)in_d0 >> 0x20);
  uVar6 = local_18._4_4_ & 0x7fffffff;
  local_18._0_4_ = (int)in_d0;
  if ((int)uVar6 < DAT_0800b480) {
    if ((int)uVar6 < DAT_0800b498) {
      if ((int)uVar6 < DAT_0800b49c) {
        iVar2 = FUN_0800ad8c((int)local_18,local_18._4_4_);
        if (iVar2 != 4) {
          return (int)local_18;
        }
        FUN_0800ca70();
        return (int)local_18;
      }
      iVar2 = -1;
      local_18 = in_d0;
    }
    else {
      uVar9 = FUN_080100e8((int)local_18,local_18._4_4_);
      uVar3 = (undefined4)((ulonglong)uVar9 >> 0x20);
      uVar1 = (undefined4)uVar9;
      uVar5 = (undefined4)DAT_0800b4a8;
      uVar8 = (undefined4)((ulonglong)DAT_0800b4a8 >> 0x20);
      if ((int)uVar6 < DAT_0800b4a0) {
        if ((int)uVar6 < DAT_0800b4b0) {
          iVar2 = 0;
          uVar4 = (undefined4)((ulonglong)DAT_0800b4b8 >> 0x20);
          uVar7 = (undefined4)DAT_0800b4b8;
          uVar9 = FUN_080054ca(uVar1,uVar3,uVar7,uVar4);
          uVar10 = FUN_08005618(uVar1,uVar3,uVar7,uVar4);
          uVar10 = FUN_0800560c((int)uVar10,(int)((ulonglong)uVar10 >> 0x20),uVar5,uVar8);
          local_18 = FUN_080056fc((int)uVar10,(int)((ulonglong)uVar10 >> 0x20),(int)uVar9,
                                  (int)((ulonglong)uVar9 >> 0x20));
        }
        else {
          iVar2 = 1;
          uVar9 = FUN_080054ca(uVar1,uVar3,uVar5,uVar8);
          uVar10 = FUN_0800560c(uVar1,uVar3,uVar5,uVar8);
          local_18 = FUN_080056fc((int)uVar10,(int)((ulonglong)uVar10 >> 0x20),(int)uVar9,
                                  (int)((ulonglong)uVar9 >> 0x20));
        }
      }
      else if ((int)uVar6 < DAT_0800b4c0) {
        iVar2 = 2;
        uVar4 = (undefined4)((ulonglong)DAT_0800b4c8 >> 0x20);
        uVar7 = (undefined4)DAT_0800b4c8;
        uVar9 = FUN_08005618(uVar1,uVar3,uVar7,uVar4);
        uVar9 = FUN_080054ca((int)uVar9,(int)((ulonglong)uVar9 >> 0x20),uVar5,uVar8);
        uVar10 = FUN_0800560c(uVar1,uVar3,uVar7,uVar4);
        local_18 = FUN_080056fc((int)uVar10,(int)((ulonglong)uVar10 >> 0x20),(int)uVar9,
                                (int)((ulonglong)uVar9 >> 0x20));
      }
      else {
        iVar2 = 3;
        local_18 = FUN_080056fc((int)DAT_0800b4d0,(int)((ulonglong)DAT_0800b4d0 >> 0x20),uVar1,uVar3
                               );
      }
    }
    uVar5 = (undefined4)((ulonglong)local_18 >> 0x20);
    uVar4 = (undefined4)local_18;
    uVar9 = FUN_08005618(uVar4,uVar5,uVar4,uVar5);
    uVar8 = (undefined4)((ulonglong)uVar9 >> 0x20);
    uVar1 = (undefined4)uVar9;
    uVar9 = FUN_08005618(uVar1,uVar8,uVar1,uVar8);
    uVar3 = (undefined4)uVar9;
    uVar7 = FUN_0800c820(uVar3,DAT_0800b4d8 + 0x800b3ae,6);
    uVar10 = FUN_08005618(uVar7,extraout_s1,uVar1,uVar8);
    uVar1 = (undefined4)((ulonglong)uVar10 >> 0x20);
    uVar8 = FUN_0800c820(uVar3,DAT_0800b4dc + 0x800b3d0,5);
    uVar9 = FUN_08005618(uVar8,extraout_s1_00,uVar3,(int)((ulonglong)uVar9 >> 0x20));
    uVar3 = (undefined4)((ulonglong)uVar9 >> 0x20);
    if (iVar2 < 0) {
      uVar9 = FUN_080054ca((int)uVar10,uVar1,(int)uVar9,uVar3);
      uVar9 = FUN_08005618((int)uVar9,(int)((ulonglong)uVar9 >> 0x20),uVar4,uVar5);
      iVar2 = FUN_08005612((int)uVar9,(int)((ulonglong)uVar9 >> 0x20),uVar4,uVar5);
    }
    else {
      uVar9 = FUN_080054ca((int)uVar10,uVar1,(int)uVar9,uVar3);
      uVar10 = FUN_08005618((int)uVar9,(int)((ulonglong)uVar9 >> 0x20),uVar4,uVar5);
      uVar9 = *(undefined8 *)(DAT_0800b4e0 + 0x800b426 + iVar2 * 8);
      uVar9 = FUN_0800560c((int)uVar10,(int)((ulonglong)uVar10 >> 0x20),(int)uVar9,
                           (int)((ulonglong)uVar9 >> 0x20));
      uVar10 = FUN_0800560c((int)uVar9,(int)((ulonglong)uVar9 >> 0x20),uVar4,uVar5);
      uVar9 = *(undefined8 *)(DAT_0800b4e4 + 0x800b44e + iVar2 * 8);
      iVar2 = FUN_08005612((int)uVar10,(int)((ulonglong)uVar10 >> 0x20),(int)uVar9,
                           (int)((ulonglong)uVar9 >> 0x20));
      if (-1 < in_d0) {
        return iVar2;
      }
    }
    return iVar2;
  }
  if (((int)uVar6 <= (int)DAT_0800b484) && ((uVar6 != DAT_0800b484 || ((int)local_18 == 0)))) {
    if (0 < (int)local_18._4_4_) {
      in_d0 = DAT_0800b488;
    }
    iVar2 = (int)in_d0;
    if ((int)local_18._4_4_ < 1) {
      iVar2 = (int)DAT_0800b490;
    }
    return iVar2;
  }
  iVar2 = FUN_080054ca((int)local_18,local_18._4_4_,(int)local_18,local_18._4_4_);
  return iVar2;
}


/* 0800b4e8 FUN_0800b4e8 */

undefined4 FUN_0800b4e8(undefined4 param_1)

{
  return param_1;
}


/* 0800b500 FUN_0800b500 */

int FUN_0800b500(void)

{
  bool bVar1;
  ulonglong uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  undefined4 uVar10;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 extraout_r1_02;
  undefined4 extraout_r1_03;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 unaff_r4;
  int iVar13;
  uint uVar14;
  uint uVar15;
  undefined4 unaff_lr;
  undefined1 uVar16;
  char cVar17;
  undefined1 uVar18;
  undefined4 uVar19;
  undefined4 uVar20;
  ulonglong in_d0;
  undefined4 extraout_s1;
  undefined4 extraout_s1_00;
  ulonglong in_d1;
  ulonglong uVar21;
  undefined4 uVar22;
  undefined8 uVar23;
  undefined8 uVar24;
  undefined8 uVar25;
  ulonglong uVar26;
  undefined8 uVar27;
  undefined8 uVar28;
  longlong lVar29;
  int local_b8;
  undefined4 uStack_a4;
  undefined4 local_a0;
  undefined4 local_90;
  undefined4 uStack_8c;
  undefined4 local_88;
  int local_30;
  uint uStack_2c;
  uint local_28;
  uint uStack_24;
  
  uVar5 = DAT_0800b930;
  uVar21 = DAT_0800b928;
  uStack_2c = (uint)(in_d0 >> 0x20);
  local_28 = (uint)in_d1;
  uStack_24 = (uint)(in_d1 >> 0x20);
  local_30 = (int)in_d0;
  uVar14 = uStack_2c & 0x7fffffff;
  uVar15 = uStack_24 & 0x7fffffff;
  if (((uint)(local_30 != 0) + uStack_2c * 2 + DAT_0800b920 < (uint)(DAT_0800b920 >> 1)) ||
     ((uint)(local_28 != 0) + uStack_24 * 2 + DAT_0800b920 < DAT_0800b924)) goto LAB_0800ca1c;
  iVar6 = (int)DAT_0800b928;
  if ((in_d1 & 0x7fffffff00000000) == 0 && local_28 == 0) {
    return iVar6;
  }
  if (uStack_2c == DAT_0800b930) {
    if (local_30 == 0) {
      return iVar6;
    }
LAB_0800b570:
    iVar7 = 1;
  }
  else {
    if (local_30 != 0) goto LAB_0800b570;
    iVar7 = 0;
  }
  if ((0xffe00000 < iVar7 + uStack_2c * 2) ||
     (uVar8 = (uint)(local_28 != 0) + uStack_24 * 2, 0xffe00000 < uVar8)) {
LAB_0800ca1c:
    iVar6 = FUN_080054ca(local_30,uStack_2c,local_28,uStack_24);
    return iVar6;
  }
  iVar7 = 0;
  if ((longlong)in_d0 < 0) {
    uVar8 = DAT_0800b934;
  }
  if ((longlong)in_d0 < 0 && (int)uVar15 < (int)uVar8) {
    if ((int)uVar15 < DAT_0800b938) {
      if ((int)DAT_0800b930 <= (int)uVar15) {
        iVar9 = DAT_0800b93c + ((int)uVar15 >> 0x14);
        if (iVar9 < 0x15) {
          if ((local_28 == 0) &&
             (uVar8 = uVar15 >> (0x14U - iVar9 & 0xff), uVar8 << (0x14U - iVar9 & 0xff) == uVar15))
          goto LAB_0800b5ee;
        }
        else {
          uVar8 = local_28 >> (0x34U - iVar9 & 0xff);
          if (uVar8 << (0x34U - iVar9 & 0xff) == local_28) {
LAB_0800b5ee:
            iVar7 = 2 - (uVar8 & 1);
          }
        }
      }
    }
    else {
      iVar7 = 2;
    }
  }
  if (((in_d0 & 0x7fffffff00000000) == 0 && local_30 == 0) && ((longlong)in_d1 < 0)) {
    if ((uStack_2c != 0 && iVar7 != 2) && (iVar7 == 1)) {
      FUN_0800ccf8(2);
      iVar6 = FUN_0800c9d8();
      return iVar6;
    }
    FUN_0800ccf8(2);
    iVar6 = FUN_0800c9d8();
    return iVar6;
  }
  uVar4 = (undefined4)(DAT_0800b928 >> 0x20);
  uVar2 = (ulonglong)DAT_0800b940 >> 0x20;
  local_b8 = (int)DAT_0800b940;
  iVar9 = (int)DAT_0800b948;
  if (local_28 == 0) {
    if (uVar15 == DAT_0800b934) {
      if (in_d0 == 0xbff0000000000000) {
        return iVar6;
      }
      if ((int)uVar14 < (int)DAT_0800b930) {
        if ((longlong)in_d1 < 0) {
          return 0;
        }
      }
      else {
        if (-1 < (longlong)in_d1) {
          in_d0 = in_d1;
        }
        if (-1 < (longlong)in_d1) {
          return (int)in_d0;
        }
      }
      return (int)*(undefined8 *)(DAT_0800b950 + 0x800b69a);
    }
    if (uVar15 == DAT_0800b930) {
      if ((longlong)in_d1 < 0) {
        if ((in_d0 & 0x7fffffff00000000) == 0) {
          if (local_30 != 0) {
            FUN_0800ccf8(2);
            iVar6 = FUN_0800ca50();
            return iVar6;
          }
          return local_b8;
        }
        if (uVar14 == DAT_0800b934) {
          if (local_30 == 0) {
            return iVar9;
          }
        }
        else if ((int)uVar14 < (int)DAT_0800b934) {
          iVar6 = FUN_080056fc(iVar6,uVar4,local_30,uStack_2c);
          return iVar6;
        }
      }
      return local_30;
    }
    if ((int)uVar14 < (int)DAT_0800b934) {
      uVar26 = in_d0;
      if (uStack_24 == 0x40000000) goto LAB_0800c0f8;
      if ((uStack_24 == 0x3fe00000) && (-1 < (longlong)in_d0)) {
        iVar6 = FUN_08012dc8(local_30,uStack_2c);
        return iVar6;
      }
    }
  }
  uVar23 = FUN_080100e8(local_30,uStack_2c);
  uVar10 = (undefined4)((ulonglong)uVar23 >> 0x20);
  uVar3 = (undefined4)uVar23;
  uVar26 = CONCAT44(uStack_2c,uVar3) & 0x7fffffffffffffff;
  if (local_30 == 0) {
    if ((in_d0 & 0x7fffffff00000000) == 0) {
      if (iVar7 == 2 || uStack_2c == 0) {
        return iVar9;
      }
      if (iVar7 != 1) {
        return iVar9;
      }
      if (-1 < (longlong)in_d0) {
        return iVar9;
      }
      return (int)DAT_0800b958;
    }
    if (uVar14 == 0x7ff00000) {
      if ((0xffffffff < (longlong)in_d0) && (-1 < (longlong)in_d1)) {
        return local_b8;
      }
      if ((0xffffffff < (longlong)in_d0) && ((longlong)in_d1 < 0)) {
        return iVar9;
      }
      if (((longlong)in_d0 < 0) && (-1 < (longlong)in_d1)) {
        if (iVar7 == 1) {
          return (int)DAT_0800b960;
        }
        return local_b8;
      }
      if ((longlong)in_d0 < 0 && (longlong)in_d1 < 0) {
        if (iVar7 != 1) {
          return iVar9;
        }
        return (int)DAT_0800b958;
      }
    }
    else if (uVar14 == uVar5) {
      if ((-1 < (longlong)in_d0) || (iVar7 != 0)) {
        if (iVar7 == 2) {
          uVar4 = 1;
        }
        else {
          uVar4 = 0xffffffff;
        }
        iVar6 = FUN_080057da(uVar4);
        return iVar6;
      }
      goto LAB_0800b84e;
    }
  }
  if ((longlong)in_d0 < 0 && iVar7 == 0) {
LAB_0800b84e:
    FUN_0800ccf8(1);
    uVar4 = (undefined4)((ulonglong)DAT_0800ca48 >> 0x20);
    iVar6 = FUN_080056fc((int)DAT_0800ca48,uVar4,(int)DAT_0800ca48,uVar4,unaff_r4,unaff_lr);
    return iVar6;
  }
  if ((longlong)in_d0 < 0 && iVar7 == 1) {
    uVar21 = DAT_0800b968;
  }
  if (DAT_0800b970 < (int)uVar15) {
    if (DAT_0800b974 < (int)uVar15) {
      if (DAT_0800b978 < (int)uVar14) {
        if ((int)uVar14 < (int)uVar5) goto LAB_0800b86e;
joined_r0x0800b87e:
        if (0 < (int)uStack_24) goto LAB_0800b880;
        goto LAB_0800b8ae;
      }
    }
    else {
LAB_0800b86e:
      if (DAT_0800b978 <= (int)uVar14) {
        if ((int)uVar5 < (int)uVar14) goto joined_r0x0800b87e;
        uVar23 = FUN_0800560c(uVar3,uVar10,iVar6,uVar4);
        uVar10 = (undefined4)((ulonglong)uVar23 >> 0x20);
        uVar3 = (undefined4)uVar23;
        uVar23 = FUN_08005618(uVar3,uVar10,(int)DAT_0800b980,(int)((ulonglong)DAT_0800b980 >> 0x20))
        ;
        uVar23 = FUN_08005612((int)uVar23,(int)((ulonglong)uVar23 >> 0x20),(int)DAT_0800b988,
                              (int)((ulonglong)DAT_0800b988 >> 0x20));
        uVar23 = FUN_08005618((int)uVar23,(int)((ulonglong)uVar23 >> 0x20),uVar3,uVar10);
        uVar23 = FUN_08005612((int)uVar23,(int)((ulonglong)uVar23 >> 0x20),(int)DAT_0800b990,
                              (int)((ulonglong)DAT_0800b990 >> 0x20));
        uVar24 = FUN_08005618(uVar3,uVar10,uVar3,uVar10);
        uVar23 = FUN_08005618((int)uVar24,(int)((ulonglong)uVar24 >> 0x20),(int)uVar23,
                              (int)((ulonglong)uVar23 >> 0x20));
        uVar24 = FUN_08005618(uVar3,uVar10,(int)DAT_0800bdb8,(int)((ulonglong)DAT_0800bdb8 >> 0x20))
        ;
        uVar20 = (undefined4)((ulonglong)uVar24 >> 0x20);
        uVar23 = FUN_08005618((int)uVar23,(int)((ulonglong)uVar23 >> 0x20),(int)DAT_0800bdc0,
                              (int)((ulonglong)DAT_0800bdc0 >> 0x20));
        uVar25 = FUN_08005618(uVar3,uVar10,(int)DAT_0800bdc8,(int)((ulonglong)DAT_0800bdc8 >> 0x20))
        ;
        uVar23 = FUN_0800560c((int)uVar25,(int)((ulonglong)uVar25 >> 0x20),(int)uVar23,
                              (int)((ulonglong)uVar23 >> 0x20));
        uVar3 = (undefined4)((ulonglong)uVar23 >> 0x20);
        FUN_080054ca((int)uVar24,uVar20,(int)uVar23,uVar3);
        uVar24 = FUN_0800560c(0,extraout_r1,(int)uVar24,uVar20);
        uVar23 = FUN_08005612((int)uVar24,(int)((ulonglong)uVar24 >> 0x20),(int)uVar23,uVar3);
        uStack_a4 = extraout_r1;
        goto LAB_0800bd7c;
      }
    }
    if ((longlong)in_d1 < 0) {
LAB_0800b880:
      FUN_0800ccf8(2);
      iVar6 = FUN_0800ca50();
      FUN_08005618((int)uVar21,(int)(uVar21 >> 0x20),local_b8,(int)uVar2);
      return iVar6;
    }
    goto LAB_0800b8ae;
  }
  iVar7 = 0;
  if (uVar14 < 0x100000) {
    uVar26 = FUN_08005618(uVar3,uVar10,(int)DAT_0800bdd0,(int)((ulonglong)DAT_0800bdd0 >> 0x20));
    iVar7 = -0x35;
  }
  uVar5 = (uint)(uVar26 >> 0x20);
  local_88 = (undefined4)uVar26;
  iVar7 = iVar7 + ((int)uVar5 >> 0x14);
  iVar9 = iVar7 + -0x3ff;
  uVar5 = uVar5 & 0xfffff;
  uVar14 = uVar5 | 0x3ff00000;
  if (DAT_0800bdd8 < (int)uVar5) {
    if ((int)uVar5 < DAT_0800bddc) {
      iVar13 = 1;
    }
    else {
      iVar13 = 0;
      uVar14 = uVar14 - 0x100000;
      iVar9 = iVar7 + -0x3fe;
    }
  }
  else {
    iVar13 = 0;
  }
  uVar23 = *(undefined8 *)(DAT_0800bde0 + 0x800ba96 + iVar13 * 8);
  uVar11 = (undefined4)((ulonglong)uVar23 >> 0x20);
  uVar19 = (undefined4)uVar23;
  uVar23 = FUN_0800560c(local_88,uVar14,uVar19,uVar11);
  uVar10 = (undefined4)((ulonglong)uVar23 >> 0x20);
  uVar24 = FUN_080054ca(local_88,uVar14,uVar19,uVar11);
  uVar24 = FUN_080056fc(iVar6,uVar4,(int)uVar24,(int)((ulonglong)uVar24 >> 0x20));
  uVar20 = (undefined4)((ulonglong)uVar24 >> 0x20);
  uVar25 = FUN_08005618((int)uVar23,uVar10,(int)uVar24,uVar20);
  uVar12 = (undefined4)((ulonglong)uVar25 >> 0x20);
  uVar3 = (undefined4)uVar25;
  iVar7 = ((int)uVar14 >> 1 | 0x20000000U) + iVar13 * 0x40000 + 0x80000;
  local_a0 = (undefined4)*(undefined8 *)(DAT_0800bde4 + 0x800baf0);
  uVar25 = FUN_0800560c(local_a0,iVar7,uVar19,uVar11);
  uVar25 = FUN_08005612((int)uVar25,(int)((ulonglong)uVar25 >> 0x20),local_88,uVar14);
  uVar25 = FUN_08005618(0,uVar12,(int)uVar25,(int)((ulonglong)uVar25 >> 0x20));
  uVar27 = FUN_08005618(0,uVar12,local_a0,iVar7);
  uVar23 = FUN_08005612((int)uVar27,(int)((ulonglong)uVar27 >> 0x20),(int)uVar23,uVar10);
  uVar23 = FUN_0800560c((int)uVar23,(int)((ulonglong)uVar23 >> 0x20),(int)uVar25,
                        (int)((ulonglong)uVar25 >> 0x20));
  uVar23 = FUN_08005618((int)uVar23,(int)((ulonglong)uVar23 >> 0x20),(int)uVar24,uVar20);
  uVar20 = (undefined4)((ulonglong)uVar23 >> 0x20);
  uVar24 = FUN_08005618(uVar3,uVar12,uVar3,uVar12);
  uVar11 = (undefined4)((ulonglong)uVar24 >> 0x20);
  uVar10 = (undefined4)uVar24;
  uVar19 = FUN_0800c820(uVar10,DAT_0800bde8 + 0x800bb8e,6);
  uVar24 = FUN_08005618(uVar10,uVar11,uVar10,uVar11);
  uVar24 = FUN_08005618((int)uVar24,(int)((ulonglong)uVar24 >> 0x20),uVar19,extraout_s1);
  uVar25 = FUN_080054ca(0,uVar12,uVar3,uVar12);
  uVar25 = FUN_08005618((int)uVar25,(int)((ulonglong)uVar25 >> 0x20),(int)uVar23,uVar20);
  uVar24 = FUN_080054ca((int)uVar25,(int)((ulonglong)uVar25 >> 0x20),(int)uVar24,
                        (int)((ulonglong)uVar24 >> 0x20));
  uVar10 = (undefined4)((ulonglong)uVar24 >> 0x20);
  uVar25 = FUN_08005618(0,uVar12,0,uVar12);
  uVar11 = (undefined4)((ulonglong)uVar25 >> 0x20);
  uVar19 = (undefined4)((ulonglong)DAT_0800bdf0 >> 0x20);
  uVar22 = (undefined4)DAT_0800bdf0;
  uVar27 = FUN_080054ca((int)uVar25,uVar11,uVar22,uVar19);
  FUN_080054ca((int)uVar27,(int)((ulonglong)uVar27 >> 0x20),(int)uVar24,uVar10);
  uVar27 = FUN_0800560c(0,extraout_r1_00,uVar22,uVar19);
  uVar25 = FUN_0800560c((int)uVar27,(int)((ulonglong)uVar27 >> 0x20),(int)uVar25,uVar11);
  uVar24 = FUN_08005612((int)uVar25,(int)((ulonglong)uVar25 >> 0x20),(int)uVar24,uVar10);
  uVar25 = FUN_08005618(0,uVar12,0,extraout_r1_00);
  uVar10 = (undefined4)((ulonglong)uVar25 >> 0x20);
  uVar24 = FUN_08005618((int)uVar24,(int)((ulonglong)uVar24 >> 0x20),uVar3,uVar12);
  uVar23 = FUN_08005618((int)uVar23,uVar20,0,extraout_r1_00);
  uVar23 = FUN_080054ca((int)uVar23,(int)((ulonglong)uVar23 >> 0x20),(int)uVar24,
                        (int)((ulonglong)uVar24 >> 0x20));
  uVar3 = (undefined4)((ulonglong)uVar23 >> 0x20);
  FUN_080054ca((int)uVar25,uVar10,(int)uVar23,uVar3);
  uVar24 = FUN_0800560c(0,extraout_r1_01,(int)uVar25,uVar10);
  uVar23 = FUN_08005612((int)uVar24,(int)((ulonglong)uVar24 >> 0x20),(int)uVar23,uVar3);
  uVar24 = FUN_08005618(0,extraout_r1_01,(int)DAT_0800bdf8,(int)((ulonglong)DAT_0800bdf8 >> 0x20));
  uVar3 = (undefined4)((ulonglong)uVar24 >> 0x20);
  uVar23 = FUN_08005618((int)uVar23,(int)((ulonglong)uVar23 >> 0x20),(int)DAT_0800be00,
                        (int)((ulonglong)DAT_0800be00 >> 0x20));
  uVar25 = FUN_08005618(0,extraout_r1_01,(int)DAT_0800be08,(int)((ulonglong)DAT_0800be08 >> 0x20));
  uVar25 = FUN_080054ca((int)uVar25,(int)((ulonglong)uVar25 >> 0x20),(int)uVar23,
                        (int)((ulonglong)uVar23 >> 0x20));
  uVar23 = *(undefined8 *)(DAT_0800be10 + 0x800bcf2 + iVar13 * 8);
  uVar25 = FUN_080054ca((int)uVar25,(int)((ulonglong)uVar25 >> 0x20),(int)uVar23,
                        (int)((ulonglong)uVar23 >> 0x20));
  uVar10 = (undefined4)((ulonglong)uVar25 >> 0x20);
  uVar27 = FUN_080057da(iVar9);
  uVar20 = (undefined4)((ulonglong)uVar27 >> 0x20);
  uVar28 = FUN_080054ca((int)uVar24,uVar3,(int)uVar25,uVar10);
  uVar23 = *(undefined8 *)(DAT_0800be14 + 0x800bd28 + iVar13 * 8);
  uVar12 = (undefined4)((ulonglong)uVar23 >> 0x20);
  uVar11 = (undefined4)uVar23;
  uVar23 = FUN_080054ca((int)uVar28,(int)((ulonglong)uVar28 >> 0x20),uVar11,uVar12);
  FUN_080054ca((int)uVar23,(int)((ulonglong)uVar23 >> 0x20),(int)uVar27,uVar20);
  uVar23 = FUN_0800560c(0,extraout_r1_02,(int)uVar27,uVar20);
  uVar23 = FUN_0800560c((int)uVar23,(int)((ulonglong)uVar23 >> 0x20),uVar11,uVar12);
  uVar23 = FUN_0800560c((int)uVar23,(int)((ulonglong)uVar23 >> 0x20),(int)uVar24,uVar3);
  uVar23 = FUN_08005612((int)uVar23,(int)((ulonglong)uVar23 >> 0x20),(int)uVar25,uVar10);
  uStack_a4 = extraout_r1_02;
LAB_0800bd7c:
  lVar29 = (ulonglong)uStack_24 << 0x20;
  uVar23 = FUN_08005618(local_28,uStack_24,(int)uVar23,(int)((ulonglong)uVar23 >> 0x20),0,uStack_24)
  ;
  uVar24 = FUN_0800560c(local_28,uStack_24,(int)lVar29,(int)((ulonglong)lVar29 >> 0x20));
  uVar24 = FUN_08005618((int)uVar24,(int)((ulonglong)uVar24 >> 0x20),0,uStack_a4);
  uVar23 = FUN_080054ca((int)uVar24,(int)((ulonglong)uVar24 >> 0x20),(int)uVar23,
                        (int)((ulonglong)uVar23 >> 0x20));
  uVar20 = (undefined4)((ulonglong)uVar23 >> 0x20);
  uVar3 = (undefined4)uVar23;
  uVar23 = FUN_08005618((int)lVar29,(int)((ulonglong)lVar29 >> 0x20),0,uStack_a4);
  uVar12 = (undefined4)((ulonglong)uVar23 >> 0x20);
  uVar10 = (undefined4)uVar23;
  lVar29 = FUN_080054ca(uVar3,uVar20,uVar10,uVar12);
  uVar5 = (uint)((ulonglong)lVar29 >> 0x20);
  iVar7 = (int)lVar29;
  if ((int)uVar5 < (int)DAT_0800c100) {
    uVar18 = DAT_0800c110 <= (uVar5 & 0x7fffffff);
    if ((bool)uVar18) {
      bVar1 = DAT_0800c114 + uVar5 == 0;
      uVar16 = iVar7 == 0 && bVar1;
      if (iVar7 != 0 || !bVar1) {
LAB_0800b8ae:
        FUN_0800ccf8(2);
        iVar6 = FUN_0800ca70();
        return iVar6;
      }
      uVar24 = FUN_0800560c(iVar7,uVar5,uVar10,uVar12);
      FUN_080058ac((int)uVar24,(int)((ulonglong)uVar24 >> 0x20),uVar3,uVar20);
      if (!(bool)uVar18 || (bool)uVar16) goto LAB_0800b8ae;
    }
  }
  else {
    cVar17 = DAT_0800c100 <= uVar5;
    if (iVar7 != 0 || uVar5 != DAT_0800c100) {
LAB_0800be94:
      FUN_0800ccf8(2);
      iVar6 = FUN_0800ca50();
      return iVar6;
    }
    uVar24 = FUN_0800560c(iVar7,uVar5,uVar10,uVar12);
    uVar25 = FUN_080054ca(uVar3,uVar20,(int)DAT_0800c108,(int)((ulonglong)DAT_0800c108 >> 0x20));
    FUN_080058ac((int)uVar25,(int)((ulonglong)uVar25 >> 0x20),(int)uVar24,
                 (int)((ulonglong)uVar24 >> 0x20));
    if (cVar17 == '\0') goto LAB_0800be94;
  }
  uVar14 = 0;
  if (DAT_0800c11c < (int)(uVar5 & 0x7fffffff)) {
    uVar5 = (0x100000U >> (DAT_0800c118 + ((int)(uVar5 & 0x7fffffff) >> 0x14) + 1U & 0xff)) + uVar5;
    uVar15 = (uVar5 * 2 >> 0x15) - 0x3ff;
    uVar14 = (uVar5 & 0xfffff | 0x100000) >> (0x14 - uVar15 & 0xff);
    local_a0 = (undefined4)*(undefined8 *)(DAT_0800c120 + 0x800bf18);
    if (lVar29 < 0) {
      uVar14 = -uVar14;
    }
    uVar23 = FUN_0800560c(uVar10,uVar12,local_a0,uVar5 & ~(DAT_0800c124 >> (uVar15 & 0xff)));
  }
  uStack_8c = (undefined4)((ulonglong)uVar23 >> 0x20);
  local_90 = (undefined4)uVar23;
  FUN_080054ca(uVar3,uVar20,local_90,uStack_8c);
  uVar23 = FUN_08005618(0,extraout_r1_03,(int)DAT_0800c128,(int)((ulonglong)DAT_0800c128 >> 0x20));
  uVar10 = (undefined4)((ulonglong)uVar23 >> 0x20);
  uVar24 = FUN_08005618(0,extraout_r1_03,(int)DAT_0800c130,(int)((ulonglong)DAT_0800c130 >> 0x20));
  uVar25 = FUN_0800560c(0,extraout_r1_03,local_90,uStack_8c);
  uVar25 = FUN_08005612((int)uVar25,(int)((ulonglong)uVar25 >> 0x20),uVar3,uVar20);
  uVar25 = FUN_08005618((int)uVar25,(int)((ulonglong)uVar25 >> 0x20),(int)DAT_0800c138,
                        (int)((ulonglong)DAT_0800c138 >> 0x20));
  uVar24 = FUN_080054ca((int)uVar25,(int)((ulonglong)uVar25 >> 0x20),(int)uVar24,
                        (int)((ulonglong)uVar24 >> 0x20));
  uVar20 = (undefined4)((ulonglong)uVar24 >> 0x20);
  uVar25 = FUN_080054ca((int)uVar23,uVar10,(int)uVar24,uVar20);
  uVar12 = (undefined4)((ulonglong)uVar25 >> 0x20);
  uVar3 = (undefined4)uVar25;
  uVar23 = FUN_0800560c(uVar3,uVar12,(int)uVar23,uVar10);
  uVar23 = FUN_08005612((int)uVar23,(int)((ulonglong)uVar23 >> 0x20),(int)uVar24,uVar20);
  uVar10 = (undefined4)((ulonglong)uVar23 >> 0x20);
  uVar24 = FUN_08005618(uVar3,uVar12,uVar3,uVar12);
  uVar20 = FUN_0800c820((int)uVar24,DAT_0800c140 + 0x800c020,5);
  uVar24 = FUN_08005618(uVar20,extraout_s1_00,(int)uVar24,(int)((ulonglong)uVar24 >> 0x20));
  uVar24 = FUN_08005612((int)uVar24,(int)((ulonglong)uVar24 >> 0x20),uVar3,uVar12);
  uVar20 = (undefined4)((ulonglong)uVar24 >> 0x20);
  uVar25 = FUN_08005618(uVar3,uVar12,(int)uVar23,uVar10);
  uVar23 = FUN_080054ca((int)uVar25,(int)((ulonglong)uVar25 >> 0x20),(int)uVar23,uVar10);
  uVar25 = FUN_0800560c((int)uVar24,uVar20,(int)DAT_0800c148,(int)((ulonglong)DAT_0800c148 >> 0x20))
  ;
  uVar24 = FUN_08005618(uVar3,uVar12,(int)uVar24,uVar20);
  uVar24 = FUN_080056fc((int)uVar24,(int)((ulonglong)uVar24 >> 0x20),(int)uVar25,
                        (int)((ulonglong)uVar25 >> 0x20));
  uVar23 = FUN_0800560c((int)uVar24,(int)((ulonglong)uVar24 >> 0x20),(int)uVar23,
                        (int)((ulonglong)uVar23 >> 0x20));
  uVar23 = FUN_0800560c((int)uVar23,(int)((ulonglong)uVar23 >> 0x20),uVar3,uVar12);
  uVar23 = FUN_08005612((int)uVar23,(int)((ulonglong)uVar23 >> 0x20),iVar6,uVar4);
  iVar7 = (int)((ulonglong)uVar23 >> 0x20);
  uVar4 = (undefined4)uVar23;
  iVar6 = iVar7 + uVar14 * 0x100000;
  in_d0 = CONCAT44(iVar6,uVar4);
  uVar26 = uVar21;
  if (iVar6 >> 0x14 < 1) {
    FUN_08005b2c(uVar4,iVar7,uVar14);
    iVar6 = FUN_0800ad8c();
    if (iVar6 == 4) {
      FUN_0800ca70();
    }
    in_d0 = FUN_08005b2c(uVar4,iVar7,uVar14);
  }
LAB_0800c0f8:
  iVar6 = FUN_08005618((int)uVar26,(int)(uVar26 >> 0x20),(int)in_d0,(int)(in_d0 >> 0x20));
  return iVar6;
}


/* 0800c150 FUN_0800c150 */

undefined8 FUN_0800c150(uint param_1,uint param_2)

{
  uint uVar1;
  undefined8 uVar2;
  
  uVar2 = FUN_08005b5a(param_1,param_2);
  uVar1 = (uint)uVar2;
  if (uVar1 != 0) {
    uVar1 = 1;
  }
  if ((int)(0x7ff00000 - ((uVar1 | (uint)((ulonglong)uVar2 >> 0x20)) & 0x7fffffff)) < 0) {
    if (param_1 != 0) {
      param_1 = 1;
    }
    if (-1 < (int)(0x7ff00000 - ((param_2 | param_1) & 0x7fffffff))) {
      FUN_0800ccf8(1);
    }
  }
  return uVar2;
}


/* 0800c1cc FUN_0800c1cc */

void FUN_0800c1cc(void)

{
  ushort uVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  undefined2 local_2c [4];
  
  if (DAT_0800c370 <= *(float *)(*DAT_0800c36c + 0xb8) - *(float *)(*DAT_0800c36c + 8)) {
    if ((*(char *)(*DAT_0800c374 + 0x28) < 'd') && (*DAT_0800c378 == '\x01')) {
      *(short *)(*DAT_0800c36c + 0xce) =
           (short)((int)((int)*(short *)(*DAT_0800c36c + 0xce) +
                        ((uint)((int)*(short *)(*DAT_0800c36c + 0xce) >> 0x1f) >> 0x1d)) >> 3);
      *DAT_0800c378 = '\0';
    }
    if ((*(char *)(*DAT_0800c374 + 0x28) == 'd') &&
       (uVar1 = *(short *)(*DAT_0800c36c + 0xd0) + 1, *(ushort *)(*DAT_0800c36c + 0xd0) = uVar1,
       0xf < uVar1)) {
      *(undefined2 *)(*DAT_0800c36c + 0xd0) = 0;
      uVar3 = FUN_08011fa8();
      *DAT_0800c37c = uVar3;
      for (uVar8 = 0; uVar8 < 4; uVar8 = uVar8 + 1) {
        uVar2 = FUN_0800dec0(3);
        local_2c[uVar8] = uVar2;
      }
      iVar4 = FUN_080117b0(local_2c,4,2);
      iVar5 = FUN_0800de88();
      uVar8 = (uint)(iVar4 * iVar5) / 1000;
      iVar4 = FUN_0800f0d0();
      iVar6 = FUN_0800f154();
      iVar4 = (iVar6 * iVar4) / 1000;
      iVar6 = 100;
      if ((22000 < *(ushort *)*DAT_0800c374) && (*(char *)(*DAT_0800c374 + 0x20) == '\x01')) {
        iVar6 = 0x46;
      }
      if (*(short *)(*DAT_0800c36c + 0xce) < 1) {
        iVar7 = -(int)*(short *)(*DAT_0800c36c + 0xce);
      }
      else {
        iVar7 = (int)*(short *)(*DAT_0800c36c + 0xce);
      }
      if (iVar7 < iVar6) {
        if ((int)(uVar8 - iVar4) < 1) {
          iVar6 = iVar4 - uVar8;
        }
        else {
          iVar6 = uVar8 - iVar4;
        }
        if ((500 < iVar6) && (iVar6 = FUN_0800f0d0(), iVar5 - iVar6 < 200)) {
          if ((int)uVar8 < iVar4) {
            *(short *)(*DAT_0800c36c + 0xce) = *(short *)(*DAT_0800c36c + 0xce) + 2;
          }
          else {
            *(short *)(*DAT_0800c36c + 0xce) = *(short *)(*DAT_0800c36c + 0xce) + -2;
          }
          *DAT_0800c378 = '\x01';
        }
      }
    }
  }
  else {
    *(short *)(*DAT_0800c36c + 0xce) =
         (short)((int)((int)*(short *)(*DAT_0800c36c + 0xce) +
                      ((uint)((int)*(short *)(*DAT_0800c36c + 0xce) >> 0x1f) >> 0x1d)) >> 3);
  }
  return;
}


/* 0800c380 FUN_0800c380 */

void FUN_0800c380(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  uVar1 = (uint)DAT_0800c3ac[3];
  uVar2 = (uint)*DAT_0800c3ac;
  if (500 < uVar1) {
    if ((int)(uVar2 - uVar1) < 1) {
      iVar3 = uVar1 - uVar2;
    }
    else {
      iVar3 = uVar2 - uVar1;
    }
    if (iVar3 < 0x32) {
      *(uint *)(DAT_0800c3ac + 0xe) = *(uint *)(DAT_0800c3ac + 0xe) | 0x20;
    }
  }
  return;
}


/* 0800c3b0 FUN_0800c3b0 */

void FUN_0800c3b0(int param_1)

{
  if ((0xc80 < param_1) || (param_1 < 100)) {
    *(uint *)(DAT_0800c3c8 + 0x1c) = *(uint *)(DAT_0800c3c8 + 0x1c) | 4;
  }
  return;
}


/* 0800c3cc FUN_0800c3cc */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_0800c3cc(int param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  byte *pbVar2;
  undefined1 uVar3;
  undefined2 uVar4;
  int iVar5;
  
  if (param_1 < 0xc59) {
    *DAT_0800c688 = 0;
    pbVar2 = DAT_0800c68c;
    *DAT_0800c68c = *DAT_0800c68c + 1;
    if (((((*(byte *)(DAT_0800c690 + 0x1c) & 1) != 0) && (2 < *pbVar2)) &&
        ((*(byte *)(DAT_0800c690 + 0x1c) & 0x10) == 0)) &&
       ((*(byte *)(DAT_0800c690 + 0x1c) & 0x20) == 0)) {
      param_1 = 0x31b;
      param_2 = s_Found_tip__0800c6d3 + 1;
      FUN_0800f808(4,s_ctrl_task_0800c6bc,s____src_app_src_ctrl_task_c_0800c6a0,DAT_0800c69c,0x31b,
                   s_Found_tip__0800c6d3 + 1,param_3,param_4);
      *(uint *)(DAT_0800c690 + 0x1c) = *(uint *)(DAT_0800c690 + 0x1c) & 0xfffffffe;
      *(undefined1 *)(*_DAT_0800c6d0 + 0xd4) = 1;
      *(undefined4 *)(*DAT_0800c6c8 + 0xc) = 0;
      *DAT_0800c6cc = '\0';
    }
  }
  else {
    *DAT_0800c688 = *DAT_0800c688 + 1;
    *DAT_0800c68c = 0;
    if (2 < *DAT_0800c688) {
      *DAT_0800c688 = 0;
      iVar5 = DAT_0800c690;
      *(uint *)(DAT_0800c690 + 0x1c) = *(uint *)(DAT_0800c690 + 0x1c) & 0xffffffef;
      *(uint *)(iVar5 + 0x1c) = *(uint *)(iVar5 + 0x1c) & 0xffffffbf;
      if ((*(byte *)(iVar5 + 0x1c) & 1) == 0) {
        *(uint *)(iVar5 + 0x1c) = *(uint *)(iVar5 + 0x1c) | 1;
        param_1 = 0x308;
        param_2 = s_No_tip__0800c694;
        FUN_0800f808(4,s_ctrl_task_0800c6bc,s____src_app_src_ctrl_task_c_0800c6a0,DAT_0800c69c,0x308
                     ,s_No_tip__0800c694,param_3,param_4);
        *(undefined4 *)(*DAT_0800c6c8 + 0xc) = 0;
      }
      FUN_0800c380(0);
      if ((*DAT_0800c6cc == '\0') &&
         ((iVar5 = FUN_0801246c(), iVar5 != 0 || (iVar5 = FUN_08012b54(), iVar5 != 0)))) {
        *DAT_0800c6cc = '\x01';
        uVar3 = FUN_08012480();
        FUN_0800f240(uVar3);
        *(undefined1 *)(*_DAT_0800c6d0 + 0xd5) = 1;
      }
    }
  }
  if (((*(char *)(*_DAT_0800c6d0 + 0xd4) != '\0') && (iVar5 = FUN_0800d030(), iVar5 == 0)) &&
     ((*(byte *)(DAT_0800c690 + 0x1c) & 0x10) == 0)) {
    *(undefined1 *)(*_DAT_0800c6d0 + 0xd4) = 0;
    FUN_08015dd8();
  }
  if (*(char *)(*_DAT_0800c6d0 + 0xd5) != '\0') {
    *_DAT_0800c6e0 = *_DAT_0800c6e0 + 1;
    uVar4 = FUN_0800dec0(3);
    *(undefined2 *)*DAT_0800c6c8 = uVar4;
    if (3 < *_DAT_0800c6e0) {
      if ((int)((uint)*(ushort *)*DAT_0800c6c8 - (uint)*(ushort *)(*DAT_0800c6c8 + 0x3c)) < 1) {
        iVar5 = (uint)*(ushort *)(*DAT_0800c6c8 + 0x3c) - (uint)*(ushort *)*DAT_0800c6c8;
      }
      else {
        iVar5 = (uint)*(ushort *)*DAT_0800c6c8 - (uint)*(ushort *)(*DAT_0800c6c8 + 0x3c);
      }
      if (iVar5 < 1000) {
        *_DAT_0800c6e0 = 0;
        param_1 = 0x341;
        param_2 = s_set__d_cur__d__MV__OK_0800c6e3 + 1;
        FUN_0800f808(3,s_ctrl_task_0800c6bc,s____src_app_src_ctrl_task_c_0800c6a0,DAT_0800c69c,0x341
                     ,s_set__d_cur__d__MV__OK_0800c6e3 + 1,*(undefined2 *)(*DAT_0800c6c8 + 0x3c),
                     *(undefined2 *)*DAT_0800c6c8);
      }
    }
    if (5 < *_DAT_0800c6e0) {
      *_DAT_0800c6e0 = 0;
      param_1 = 0x348;
      param_2 = s_set__d_cur__d__MV__ERR_0800c6fc;
      FUN_0800f808(3,s_ctrl_task_0800c6bc,s____src_app_src_ctrl_task_c_0800c6a0,DAT_0800c69c,0x348,
                   s_set__d_cur__d__MV__ERR_0800c6fc,*(undefined2 *)(*DAT_0800c6c8 + 0x3c),
                   *(undefined2 *)*DAT_0800c6c8);
    }
    if (*_DAT_0800c6e0 == 0) {
      *(undefined1 *)(*_DAT_0800c6d0 + 0xd5) = 0;
      FUN_08015dd8();
    }
  }
  if ((*(byte *)(DAT_0800c690 + 0x1c) & 0x40) != 0) {
    cVar1 = *(char *)(*DAT_0800c6c8 + 0x20);
    if (cVar1 == '\0') {
      if ((0x707 < *(int *)(*DAT_0800c6c8 + 0xc)) && (*(int *)(*DAT_0800c6c8 + 0xc) < 0xaf1)) {
        *(uint *)(DAT_0800c690 + 0x1c) = *(uint *)(DAT_0800c690 + 0x1c) & 0xffffffbf;
      }
    }
    else if (cVar1 == '\x01') {
      if ((1999 < *(int *)(*DAT_0800c6c8 + 0xc)) && (*(int *)(*DAT_0800c6c8 + 0xc) < 0xdad)) {
        *(uint *)(DAT_0800c690 + 0x1c) = *(uint *)(DAT_0800c690 + 0x1c) & 0xffffffbf;
      }
    }
    else if (((cVar1 == '\x02') && (0x157b < *(int *)(*DAT_0800c6c8 + 0xc))) &&
            (*(int *)(*DAT_0800c6c8 + 0xc) < 0x2329)) {
      *(uint *)(DAT_0800c690 + 0x1c) = *(uint *)(DAT_0800c690 + 0x1c) & 0xffffffbf;
    }
  }
  return CONCAT44(param_2,param_1);
}


/* 0800c714 FUN_0800c714 */

void FUN_0800c714(int param_1)

{
  if (*(char *)(*DAT_0800c748 + 0xd4) == '\0') {
    if (param_1 < (int)(uint)*(ushort *)(*DAT_0800c74c + 0x58)) {
      *(uint *)(DAT_0800c750 + 0x1c) = *(uint *)(DAT_0800c750 + 0x1c) | 2;
    }
    else {
      *(uint *)(DAT_0800c750 + 0x1c) = *(uint *)(DAT_0800c750 + 0x1c) & 0xfffffffd;
    }
  }
  return;
}


/* 0800c754 FUN_0800c754 */

undefined8 FUN_0800c754(uint param_1,uint param_2,int *param_3,int param_4)

{
  short sVar1;
  short sVar2;
  
  if (*param_3 != 0) {
    sVar2 = (short)(param_1 + 0x14);
    sVar1 = (short)param_2;
    if (param_4 == 0) {
      FUN_08011138(param_1,(int)(short)(sVar1 + 2),DAT_0800c814,0x10,0x10,0x4dc,*DAT_0800c810,0);
      param_2 = (uint)*DAT_0800c810;
      param_1 = 0x4dc;
      FUN_08011500((int)(short)(sVar2 + 2),(int)(short)(sVar1 + 2),*param_3,*DAT_0800c818);
    }
    else {
      FUN_08011138(param_1,(int)(short)(sVar1 + 2),DAT_0800c81c,0x10,0x10,0x4dc,*DAT_0800c810,
                   param_4);
      FUN_080105a4(param_1 + 0x14 & 0xffff,param_2 + 1 & 0xffff,0x80,0x12,3,1,0xfc63,0xfc63);
      param_1 = (uint)*DAT_0800c810;
      param_2 = 0xfc63;
      FUN_08011500((int)(short)(sVar2 + 2),(int)(short)(sVar1 + 2),*param_3,*DAT_0800c818);
    }
  }
  return CONCAT44(param_2,param_1);
}


/* 0800c820 FUN_0800c820 */

undefined4 FUN_0800c820(undefined8 *param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined8 in_d0;
  undefined8 uVar5;
  undefined4 uVar6;
  
  uVar3 = param_2 - 1;
  uVar5 = param_1[uVar3];
  while( true ) {
    uVar4 = (undefined4)uVar5;
    uVar1 = (undefined4)((ulonglong)uVar5 >> 0x20);
    if ((uVar3 & 0xfffffff9) == 0) break;
    uVar5 = FUN_08005618(uVar4,uVar1);
    uVar3 = uVar3 - 1;
    uVar5 = FUN_080054ca((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),(int)param_1[uVar3],
                         (int)((ulonglong)param_1[uVar3] >> 0x20));
  }
  uVar6 = (undefined4)in_d0;
  uVar2 = (undefined4)((ulonglong)in_d0 >> 0x20);
  if (uVar3 != 2) {
    if (uVar3 != 4) {
      if (uVar3 != 6) {
        return uVar4;
      }
      uVar5 = FUN_08005618(uVar4,uVar1,uVar6,uVar2);
      uVar5 = FUN_080054ca((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),(int)param_1[5],
                           (int)((ulonglong)param_1[5] >> 0x20));
      uVar5 = FUN_08005618((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),uVar6,uVar2);
      uVar5 = FUN_080054ca((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),(int)param_1[4],
                           (int)((ulonglong)param_1[4] >> 0x20));
    }
    uVar5 = FUN_08005618((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),uVar6,uVar2);
    uVar5 = FUN_080054ca((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),(int)param_1[3],
                         (int)((ulonglong)param_1[3] >> 0x20));
    uVar5 = FUN_08005618((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),uVar6,uVar2);
    uVar5 = FUN_080054ca((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),(int)param_1[2],
                         (int)((ulonglong)param_1[2] >> 0x20));
  }
  uVar5 = FUN_08005618((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),uVar6,uVar2);
  uVar5 = FUN_080054ca((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),(int)param_1[1],
                       (int)((ulonglong)param_1[1] >> 0x20));
  uVar5 = FUN_08005618((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),uVar6,uVar2);
  uVar1 = FUN_080054ca((int)uVar5,(int)((ulonglong)uVar5 >> 0x20),(int)*param_1,
                       (int)((ulonglong)*param_1 >> 0x20));
  return uVar1;
}


/* 0800c918 FUN_0800c918 */

void FUN_0800c918(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*DAT_0800c934 + 4) = param_2;
  FUN_0800cbd4();
  FUN_08012418();
  if (param_1 == 0) {
    FUN_0800b030();
  }
  return;
}


/* 0800c938 FUN_0800c938 */

undefined8 FUN_0800c938(uint param_1,uint param_2,int *param_3,int param_4)

{
  short sVar1;
  short sVar2;
  
  if (*param_3 != 0) {
    sVar1 = (short)param_2;
    if (param_3[1] != 0) {
      FUN_0801103a(param_1,(int)(short)(sVar1 + 2),0x10,0x10,param_3[1],param_2,param_3,param_4);
    }
    sVar2 = (short)(param_1 + 0x14);
    if (param_4 == 0) {
      param_2 = (uint)*DAT_0800c9d0;
      param_1 = 0x4dc;
      FUN_08011500((int)(short)(sVar2 + 2),(int)(short)(sVar1 + 2),*param_3,*DAT_0800c9d4);
    }
    else {
      FUN_080105a4(param_1 + 0x14 & 0xffff,param_2 + 1 & 0xffff,0x80,0x12,3,1,0xfc63,0xfc63);
      param_1 = (uint)*DAT_0800c9d0;
      param_2 = 0xfc63;
      FUN_08011500((int)(short)(sVar2 + 2),(int)(short)(sVar1 + 2),*param_3,*DAT_0800c9d4);
    }
  }
  return CONCAT44(param_2,param_1);
}


/* 0800c9d8 FUN_0800c9d8 */

undefined4 FUN_0800c9d8(void)

{
  undefined4 uVar1;
  
  uVar1 = FUN_080056fc((int)DAT_0800ca00,(int)((ulonglong)DAT_0800ca00 >> 0x20),(int)DAT_0800c9f8,
                       (int)((ulonglong)DAT_0800c9f8 >> 0x20));
  return uVar1;
}


/* 0800ca50 FUN_0800ca50 */

undefined4 FUN_0800ca50(void)

{
  undefined4 uVar1;
  
  uVar1 = (undefined4)((ulonglong)DAT_0800ca68 >> 0x20);
  uVar1 = FUN_08005618((int)DAT_0800ca68,uVar1,(int)DAT_0800ca68,uVar1);
  return uVar1;
}


/* 0800ca70 FUN_0800ca70 */

undefined4 FUN_0800ca70(void)

{
  undefined4 uVar1;
  
  uVar1 = (undefined4)((ulonglong)DAT_0800ca88 >> 0x20);
  uVar1 = FUN_08005618((int)DAT_0800ca88,uVar1,(int)DAT_0800ca88,uVar1);
  return uVar1;
}


/* 0800ca90 FUN_0800ca90 */

void FUN_0800ca90(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = FUN_0800cbcc(param_1);
  *(undefined1 *)(param_1 + 9) = 0;
  if ((param_2 < (int)(uint)*(byte *)(param_1 + 8)) && (*(byte *)(param_1 + 8) - 1 == iVar1)) {
    *(char *)(param_1 + 9) = (char)param_2 + -1;
  }
  else if (0 < iVar1) {
    *(undefined1 *)(param_1 + 9) = 1;
  }
  return;
}


/* 0800cac4 FUN_0800cac4 */

undefined8 FUN_0800cac4(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  int iVar6;
  
  uVar1 = (uint)*DAT_0800cbc0;
  iVar6 = param_2;
  FUN_08011214(0,0,0xa0,0x28,uVar1,param_2,param_3,param_4);
  if (2 < *(byte *)(param_1 + 8)) {
    iVar6 = 1;
    FUN_080105a4(0x98,0,5,0x28,1,1,0x8430,0x8430);
    uVar2 = 0x48 / *(byte *)(param_1 + 8);
    uVar1 = 0xd69a;
    FUN_08011214(0x98,((int)(param_2 * (0x24 - uVar2)) / (int)(*(byte *)(param_1 + 8) - 1) & 0xffU)
                      + 2,5,uVar2);
  }
  if (*(byte *)(param_1 + 8) < 3) {
    uVar2 = 0;
  }
  else {
    uVar2 = param_2 - (uint)*(byte *)(param_1 + 9) & 0xff;
  }
  for (iVar3 = 0; iVar3 < 2; iVar3 = iVar3 + 1) {
    iVar4 = *(int *)(param_1 + 4) + uVar2 * 0x18 + iVar3 * 0x18;
    bVar5 = uVar2 + iVar3 == param_2;
    if (param_1 == DAT_0800cbc4) {
      FUN_0800c938(0,(int)(short)((short)iVar3 * 0x14),iVar4,bVar5);
    }
    else {
      FUN_0800c754(0,(int)(short)((short)iVar3 * 0x14),iVar4,bVar5);
    }
  }
  *DAT_0800cbc8 = *(int *)(param_1 + 4) + param_2 * 0x18;
  FUN_08011400();
  return CONCAT44(iVar6,uVar1);
}


/* 0800cbcc FUN_0800cbcc */

undefined1 FUN_0800cbcc(int param_1)

{
  return *(undefined1 *)(param_1 + 10);
}


/* 0800cbd4 FUN_0800cbd4 */

void FUN_0800cbd4(void)

{
  int iVar1;
  
  for (iVar1 = 0; iVar1 < 0x10; iVar1 = iVar1 + 1) {
    *(undefined4 *)(DAT_0800cc50 + iVar1 * 0x18) =
         *(undefined4 *)(DAT_0800cc4c + (uint)*(byte *)(*DAT_0800cc48 + 4) * 0x40 + iVar1 * 4);
  }
  for (iVar1 = 0; iVar1 < 2; iVar1 = iVar1 + 1) {
    *(undefined4 *)(DAT_0800cc58 + iVar1 * 0x18) =
         *(undefined4 *)(DAT_0800cc54 + (uint)*(byte *)(*DAT_0800cc48 + 4) * 8 + iVar1 * 4);
  }
  for (iVar1 = 0; iVar1 < 3; iVar1 = iVar1 + 1) {
    *(undefined4 *)(DAT_0800cc60 + iVar1 * 0x18) =
         *(undefined4 *)(DAT_0800cc5c + (uint)*(byte *)(*DAT_0800cc48 + 4) * 0xc + iVar1 * 4);
  }
  return;
}


/* 0800cc64 FUN_0800cc64 */

void FUN_0800cc64(int param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 10) = param_2;
  return;
}


/* 0800cc68 FUN_0800cc68 */

void FUN_0800cc68(int param_1,undefined1 param_2)

{
  *(undefined1 *)(*DAT_0800cc84 + 0x50) = param_2;
  FUN_0800f08c();
  if (param_1 == 0) {
    FUN_0800b030();
  }
  return;
}


/* 0800cc88 FUN_0800cc88 */

void FUN_0800cc88(int param_1,int param_2)

{
  if (param_2 == 2) {
    *(char *)(*DAT_0800ccc8 + 0x53) = (char)param_2;
  }
  else {
    *(char *)(*DAT_0800ccc8 + 0x52) = (char)param_2;
    FUN_080114f4(*(undefined1 *)(*DAT_0800ccc8 + 0x52));
    *(undefined1 *)(*DAT_0800ccc8 + 0x53) = 0;
  }
  FUN_0800f08c();
  if (param_1 == 0) {
    FUN_0800b030();
  }
  return;
}


/* 0800ccec FUN_0800ccec */

void FUN_0800ccec(undefined4 param_1)

{
  *DAT_0800ccf4 = param_1;
  return;
}


/* 0800ccf8 FUN_0800ccf8 */

void FUN_0800ccf8(undefined4 param_1)

{
  *DAT_0800cd00 = param_1;
  return;
}


/* 0800cd04 FUN_0800cd04 */

undefined4 FUN_0800cd04(undefined4 param_1)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined2 local_38 [20];
  
  FUN_08005ce8(DAT_0800cd70,param_1,1,6);
  for (iVar4 = 0; iVar4 < 0x14; iVar4 = iVar4 + 1) {
    FUN_08005cd8(DAT_0800cd70,0x7000);
    FUN_08005eba(DAT_0800cd70,1);
    do {
      iVar2 = FUN_08005eea(DAT_0800cd70,4);
    } while (iVar2 == 0);
    FUN_08005ca6(DAT_0800cd70,4);
    FUN_08005ca6(DAT_0800cd70,8);
    uVar1 = FUN_08005f0e(DAT_0800cd70,0x14);
    local_38[iVar4] = uVar1;
  }
  uVar3 = FUN_080117b0(local_38,0x14,10);
  return uVar3;
}


/* 0800cd74 FUN_0800cd74 */

float FUN_0800cd74(int param_1,int param_2)

{
  int iVar1;
  ushort *puVar2;
  ushort *puVar3;
  uint in_fpscr;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  
  puVar2 = (ushort *)(DAT_0800ce80 + param_2 * 0x2c + 0x16);
  puVar3 = (ushort *)(DAT_0800ce80 + param_2 * 0x2c);
  if ((int)(uint)*puVar2 < param_1) {
    iVar1 = FUN_08010cb4(puVar2,0xb,param_1);
    if (9 < iVar1) {
      iVar1 = iVar1 + -1;
    }
    fVar7 = (float)VectorUnsignedToFloat((uint)puVar3[iVar1 + 1],(byte)(in_fpscr >> 0x15) & 3);
    fVar4 = (float)VectorUnsignedToFloat((uint)puVar3[iVar1],(byte)(in_fpscr >> 0x15) & 3);
    fVar9 = (float)VectorUnsignedToFloat((uint)puVar2[iVar1 + 1],(byte)(in_fpscr >> 0x15) & 3);
    fVar5 = (float)VectorUnsignedToFloat((uint)puVar2[iVar1],(byte)(in_fpscr >> 0x15) & 3);
    fVar6 = (float)VectorUnsignedToFloat((uint)puVar3[iVar1],(byte)(in_fpscr >> 0x15) & 3);
    fVar8 = (float)VectorSignedToFloat(param_1 - (uint)puVar2[iVar1],(byte)(in_fpscr >> 0x15) & 3);
    fVar6 = fVar6 + fVar8 * ((fVar7 - fVar4) / (fVar9 - fVar5));
  }
  else {
    fVar7 = (float)VectorUnsignedToFloat((uint)*puVar3,(byte)(in_fpscr >> 0x15) & 3);
    fVar4 = (float)VectorSignedToFloat((int)*(char *)(*DAT_0800ce84 + 0x5a),
                                       (byte)(in_fpscr >> 0x15) & 3);
    fVar5 = (float)VectorUnsignedToFloat((uint)*puVar2,(byte)(in_fpscr >> 0x15) & 3);
    fVar6 = (float)VectorSignedToFloat((int)*(char *)(*DAT_0800ce84 + 0x5a),
                                       (byte)(in_fpscr >> 0x15) & 3);
    fVar8 = (float)VectorSignedToFloat(param_1,(byte)(in_fpscr >> 0x15) & 3);
    fVar6 = fVar6 + fVar8 * ((fVar7 - fVar4) / (fVar5 - DAT_0800ce88));
  }
  return fVar6;
}


/* 0800ce8c FUN_0800ce8c */

void FUN_0800ce8c(void)

{
  undefined1 uVar1;
  
  *(undefined1 *)*DAT_0800cf68 = 0;
  *(undefined1 *)(*DAT_0800cf68 + 2) = 0;
  *(undefined1 *)(*DAT_0800cf68 + 3) = 0;
  *(undefined4 *)(*DAT_0800cf68 + 0x60) = DAT_0800cf6c;
  *(undefined4 *)(*DAT_0800cf68 + 0xc0) = 100;
  FUN_0801266c(0x3f800000,DAT_0800cf70,DAT_0800cf6c,*DAT_0800cf68 + 100,*DAT_0800cf68 + 8,
               *DAT_0800cf68 + 0xbc,*DAT_0800cf68 + 0xb8,1,0);
  FUN_0801266c(DAT_0800cf78,DAT_0800cf74,DAT_0800cf6c,*DAT_0800cf68 + 0xc,*DAT_0800cf68 + 4,
               *DAT_0800cf68 + 0xbc,*DAT_0800cf68 + 0x60,1,0);
  FUN_080127e4(*DAT_0800cf68 + 100,100);
  FUN_080128dc(DAT_0800cf7c,0x41200000,*DAT_0800cf68 + 100);
  FUN_080127e4(*DAT_0800cf68 + 0xc,0x14);
  FUN_080128dc(DAT_0800cf84,DAT_0800cf80,*DAT_0800cf68 + 0xc);
  uVar1 = FUN_0801239c();
  *(undefined1 *)(*DAT_0800cf88 + 0x20) = uVar1;
  FUN_0800f3ac(*(undefined1 *)(*DAT_0800cf88 + 0x20));
  FUN_08015dd8();
  return;
}


/* 0800cf8c FUN_0800cf8c */

int FUN_0800cf8c(int param_1,int param_2,int param_3)

{
  if (param_1 != param_2) {
    param_1 = FUN_0800e13c(param_3 - (param_1 * 6 + param_2 * 10 >> 4),3);
    param_1 = param_3 - param_1;
  }
  return param_1;
}


/* 0800d030 FUN_0800d030 */

undefined4 FUN_0800d030(void)

{
  char cVar1;
  undefined1 uVar2;
  undefined2 uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  uint in_fpscr;
  undefined2 local_28 [10];
  
  if ((*(byte *)(DAT_0800d200 + 0x1c) & 0x20) != 0) {
    return 0xffffffff;
  }
  uVar6 = 0xa0;
  *DAT_0800d204 = *DAT_0800d204 + 1;
  iVar4 = FUN_08010ce8();
  if (iVar4 == 0) {
    iVar4 = FUN_0801246c();
    if ((iVar4 == 0) && (iVar4 = FUN_08012b54(), iVar4 == 0)) {
      return 0xffffffff;
    }
    if (*DAT_0800d208 == '\0') {
      *DAT_0800d208 = '\x01';
      uVar2 = FUN_08012480();
      FUN_0800f240(uVar2);
      *(undefined1 *)(*DAT_0800d20c + 0xd5) = 1;
      return 0xffffffff;
    }
    if (*(char *)(*DAT_0800d20c + 0xd5) != '\0') {
      return 0xffffffff;
    }
    *DAT_0800d208 = '\0';
  }
  if (*(char *)(*DAT_0800d210 + 0x20) == '\x02') {
    uVar6 = 1000;
  }
  if (*DAT_0800d204 < 5) {
    uVar6 = 0xffffffff;
  }
  else {
    *DAT_0800d204 = 0;
    uVar6 = VectorUnsignedToFloat(uVar6,(byte)(in_fpscr >> 0x15) & 3);
    FUN_08013310(uVar6);
    FUN_0800de78();
    *(undefined2 *)(*DAT_0800d20c + 0xd2) = 0x514;
    FUN_0800f418(5);
    for (uVar7 = 0; uVar7 < 10; uVar7 = uVar7 + 1) {
      uVar3 = FUN_0800dec0(1);
      local_28[uVar7] = uVar3;
      FUN_0800f430(500);
    }
    iVar4 = FUN_080117b0(local_28,10,3);
    iVar5 = FUN_0800de88();
    uVar7 = iVar5 - ((uint)*(ushort *)*DAT_0800d210 * 0x16) / 9000;
    *(uint *)(*DAT_0800d210 + 0xc) = (uint)(iVar4 * 1000) / uVar7;
    FUN_08013310(DAT_0800d214);
    FUN_0800f808(4,s_ctrl_task_0800d250,s____src_app_src_ctrl_task_c_0800d234,DAT_0800d230,0x2e0,
                 s_res_mohm__d_i__d_v__d_0800d218,*(undefined4 *)(*DAT_0800d210 + 0xc),uVar7,iVar4);
    cVar1 = *(char *)(*DAT_0800d210 + 0x20);
    if (cVar1 == '\0') {
      if ((*(int *)(*DAT_0800d210 + 0xc) < 0x708) || (0xaf0 < *(int *)(*DAT_0800d210 + 0xc))) {
        *(uint *)(DAT_0800d200 + 0x1c) = *(uint *)(DAT_0800d200 + 0x1c) | 0x40;
      }
    }
    else if (cVar1 == '\x01') {
      if ((*(int *)(*DAT_0800d210 + 0xc) < 2000) || (0xdac < *(int *)(*DAT_0800d210 + 0xc))) {
        *(uint *)(DAT_0800d200 + 0x1c) = *(uint *)(DAT_0800d200 + 0x1c) | 0x40;
      }
    }
    else if ((cVar1 == '\x02') &&
            ((*(int *)(*DAT_0800d210 + 0xc) < 0x157c || (9000 < *(int *)(*DAT_0800d210 + 0xc))))) {
      *(uint *)(DAT_0800d200 + 0x1c) = *(uint *)(DAT_0800d200 + 0x1c) | 0x40;
    }
    uVar6 = 0;
  }
  return uVar6;
}


/* 0800d27c FUN_0800d27c */

void FUN_0800d27c(int param_1,uint param_2)

{
  undefined1 uVar1;
  
  if ((*(char *)(DAT_0800d2b4 + 0x20) == '\0') && (param_2 != 0)) {
    param_2 = param_2 + 2 & 0xff;
  }
  *(char *)(*DAT_0800d2b8 + 0x2c) = (char)param_2;
  uVar1 = FUN_08012480();
  FUN_0800f240(uVar1);
  FUN_0800f08c();
  FUN_08015dd8();
  if (param_1 == 0) {
    FUN_0800b030();
  }
  return;
}


/* 0800d2bc FUN_0800d2bc */

void FUN_0800d2bc(short *param_1)

{
  uint in_fpscr;
  float fVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if (*(char *)(*DAT_0800d3a0 + 0x53) == '\x02') {
    uVar2 = VectorSignedToFloat((int)param_1[2],(byte)(in_fpscr >> 0x15) & 3);
    uVar3 = VectorSignedToFloat((int)param_1[1],(byte)(in_fpscr >> 0x15) & 3);
    uVar4 = VectorSignedToFloat((int)*param_1,(byte)(in_fpscr >> 0x15) & 3);
    fVar1 = (float)FUN_0800920c(uVar4,uVar3,uVar2);
    if (0.0 <= fVar1) {
      if (0.0 < fVar1) {
        *DAT_0800d3a8 = *DAT_0800d3a8 + 1;
        *DAT_0800d3a4 = 0;
        if (5 < *DAT_0800d3a8) {
          *DAT_0800d3a8 = 0;
          if (*(char *)(*DAT_0800d3a0 + 0x52) == '\0') {
            FUN_080114f4(1);
            *(undefined1 *)(*DAT_0800d3a0 + 0x52) = 1;
            FUN_08011c48();
          }
        }
      }
    }
    else {
      *DAT_0800d3a4 = *DAT_0800d3a4 + 1;
      *DAT_0800d3a8 = 0;
      if (5 < *DAT_0800d3a4) {
        *DAT_0800d3a4 = 0;
        if (*(char *)(*DAT_0800d3a0 + 0x52) != '\0') {
          FUN_080114f4(0);
          *(undefined1 *)(*DAT_0800d3a0 + 0x52) = 0;
          FUN_08011c48();
        }
      }
    }
  }
  return;
}


/* 0800d3ac FUN_0800d3ac */

void FUN_0800d3ac(int param_1)

{
  int iVar1;
  undefined4 auStack_24 [6];
  
  if (param_1 == 6) {
    param_1 = 5;
  }
  iVar1 = FUN_08010a6c(0x22,10);
  if (param_1 != iVar1) {
    FUN_08010ab2(0x22,10,param_1);
    FUN_080053ee(auStack_24,DAT_0800d400,0x18);
    FUN_0800f808(3,s_ch224q_0800d434,s____src_drivers_src_ch224q_c_0800d418,DAT_0800d414,0x165,
                 s_fixed_req__sV_0800d404,auStack_24[param_1]);
  }
  return;
}


/* 0800d43c FUN_0800d43c */

void FUN_0800d43c(int *param_1,int param_2,int param_3,uint param_4,uint param_5,int param_6)

{
  int iVar1;
  uint uVar2;
  char extraout_r2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  bool bVar9;
  undefined1 uVar10;
  longlong lVar11;
  undefined8 uVar12;
  longlong lVar13;
  
  uVar2 = 0;
  if (param_3 == 0 && param_4 == 0) {
    if (param_6 == 1) {
      uVar2 = ~param_5;
    }
    *param_1 = (int)&DAT_0800d5b4;
    param_1[1] = uVar2;
    param_1[2] = 1;
    param_1[3] = param_6;
  }
  else {
    iVar5 = (int)(((param_4 >> 0x14) - 0x3ff) * 0x4d10) >> 0x10;
    do {
      while( true ) {
        if (param_6 == 1) {
          uVar2 = -param_5;
        }
        else {
          uVar2 = (iVar5 - param_5) + 1;
        }
        lVar11 = (ulonglong)DAT_0800d5ac << 0x20;
        lVar13 = (ulonglong)DAT_0800d5b0 << 0x20;
        uVar4 = uVar2;
        if ((int)uVar2 < 0) {
          uVar4 = -uVar2;
        }
        iVar1 = DAT_0800d5b0 + uVar4 * 0x100000;
        while( true ) {
          uVar6 = (undefined4)((ulonglong)lVar11 >> 0x20);
          uVar8 = (undefined4)((ulonglong)lVar13 >> 0x20);
          uVar7 = (undefined4)lVar13;
          if (uVar4 == 0) break;
          if ((uVar4 & 1) != 0) {
            lVar13 = FUN_08005618(uVar7,uVar8,(int)lVar11,uVar6);
          }
          lVar11 = FUN_08005618((int)lVar11,uVar6);
          uVar4 = (int)uVar4 >> 1;
        }
        uVar10 = 1;
        if ((int)uVar2 < 0) {
          uVar12 = FUN_08005618();
          uVar12 = FUN_08005618((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),uVar7,uVar8);
        }
        else {
          uVar12 = FUN_080056fc(param_3,param_4,0,iVar1);
          uVar12 = FUN_080056fc((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),uVar7,uVar8);
        }
        bVar9 = true;
        FUN_080058ac();
        if ((bool)uVar10 && !bVar9) {
          FUN_080054ca((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),0,DAT_0800d5bc);
          lVar13 = FUN_08005bfc();
        }
        else {
          lVar13 = -1;
        }
        iVar1 = 0x10;
        while( true ) {
          if ((lVar13 == 0) || (iVar1 < 0)) break;
          lVar13 = FUN_08005940((int)lVar13,(int)((ulonglong)lVar13 >> 0x20),10,0);
          *(char *)(param_2 + iVar1) = extraout_r2 + '0';
          iVar1 = iVar1 + -1;
        }
        iVar3 = 0x11 - (iVar1 + 1);
        if (param_6 != 1) break;
        if (lVar13 == 0) {
          iVar5 = (iVar3 - param_5) + -1;
          goto LAB_0800d59c;
        }
        param_5 = 0x11;
        param_6 = 0;
      }
      bVar9 = true;
      if ((lVar13 == 0) && (iVar3 <= (int)param_5)) {
        if (iVar3 < (int)param_5) {
          bVar9 = false;
          iVar5 = iVar5 + -1;
        }
      }
      else {
        bVar9 = false;
        iVar5 = iVar5 + 1;
      }
    } while (!bVar9);
LAB_0800d59c:
    param_1[2] = iVar3;
    param_1[3] = param_6;
    *param_1 = iVar1 + 1 + param_2;
    param_1[1] = iVar5;
  }
  return;
}


/* 0800d5c0 FUN_0800d5c0 */

int FUN_0800d5c0(byte *param_1,uint *param_2,undefined4 param_3,code *param_4)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  char extraout_r1;
  int *piVar6;
  uint uVar7;
  char *pcVar8;
  undefined1 uVar9;
  uint *puVar10;
  int extraout_r2;
  undefined4 uVar11;
  uint uVar12;
  uint uVar13;
  int iVar14;
  byte *pbVar15;
  char *pcVar16;
  byte *pbVar17;
  uint *puVar18;
  char **unaff_r10;
  uint uVar19;
  undefined4 *puVar20;
  bool bVar21;
  bool bVar22;
  bool bVar23;
  longlong lVar24;
  char *local_88;
  undefined4 local_84;
  char **local_80;
  char *local_7c;
  char **local_78;
  uint local_74;
  undefined1 auStack_70 [32];
  char *local_50;
  char **local_4c;
  char *pcStack_48;
  int local_44;
  byte local_3b [3];
  byte *local_38;
  byte *pbStack_34;
  uint *puStack_30;
  undefined4 local_2c;
  code *pcStack_28;
  
  pcStack_28 = param_4;
  local_2c = param_3;
  puStack_30 = param_2;
  pbStack_34 = param_1;
  iVar14 = 0;
LAB_0800d9f0:
  uVar4 = (uint)*param_1;
  if (uVar4 == 0) {
    return iVar14;
  }
  if (uVar4 == 0x25) {
    uVar13 = 0;
    pcVar16 = (char *)0x0;
    local_74 = 0;
    while( true ) {
      pbVar15 = param_1 + 1;
      uVar4 = 1 << (*pbVar15 - 0x20 & 0xff);
      if ((uVar4 & DAT_0800d9bc) == 0) break;
      uVar13 = uVar13 | uVar4;
      param_1 = pbVar15;
    }
    if (*pbVar15 == 0x2a) {
      puVar10 = param_2 + 1;
      local_74 = *param_2;
      if ((int)local_74 < 0) {
        uVar13 = uVar13 | 0x2000;
        local_74 = -local_74;
      }
      uVar13 = uVar13 | 2;
      pbVar15 = param_1 + 2;
    }
    else {
      for (; puVar10 = param_2, *pbVar15 - 0x30 < 10; pbVar15 = pbVar15 + 1) {
        uVar13 = uVar13 | 2;
        local_74 = (uint)*pbVar15 + local_74 * 10 + -0x30;
      }
    }
    param_1 = pbVar15;
    puVar18 = puVar10;
    if (*pbVar15 == 0x2e) {
      param_1 = pbVar15 + 1;
      uVar13 = uVar13 | 4;
      if (*param_1 == 0x2a) {
        puVar18 = puVar10 + 1;
        pcVar16 = (char *)*puVar10;
        param_1 = pbVar15 + 2;
      }
      else {
        for (; *param_1 - 0x30 < 10; param_1 = param_1 + 1) {
          pcVar16 = (char *)((uint)*param_1 + (int)pcVar16 * 10 + -0x30);
        }
      }
    }
    bVar1 = *param_1;
    if (bVar1 == 0x6c) {
      uVar13 = uVar13 | 0x100000;
LAB_0800d696:
      if (param_1[1] == bVar1) {
        uVar13 = uVar13 + 0x100000;
        param_1 = param_1 + 1;
      }
    }
    else if (bVar1 < 0x6d) {
      if (bVar1 != 0x4c) {
        if (bVar1 == 0x68) {
          uVar13 = uVar13 | 0x300000;
          goto LAB_0800d696;
        }
        if (bVar1 != 0x6a) goto LAB_0800d6a4;
        uVar13 = uVar13 | 0x200000;
      }
    }
    else if ((bVar1 != 0x74) && (bVar1 != 0x7a)) goto LAB_0800d6a4;
    param_1 = param_1 + 1;
LAB_0800d6a4:
    uVar4 = (uint)*param_1;
    bVar23 = SBORROW4(uVar4,0x66);
    bVar21 = (int)(uVar4 - 0x66) < 0;
    bVar22 = uVar4 == 0x66;
LAB_0800d6a8:
    while (!bVar22) {
      param_2 = puVar18;
      if (!bVar22 && bVar21 == bVar23) {
        if (uVar4 == 0x70) {
          uVar13 = uVar13 | 4;
          pcVar16 = &NMI;
          local_88 = (char *)0x10;
        }
        else if (uVar4 < 0x71) {
          if (uVar4 == 0x67) break;
          if (uVar4 == 0x69) goto LAB_0800d7c2;
          if (uVar4 == 0x6e) {
            uVar4 = (uVar13 << 9) >> 0x1d;
            if (uVar4 == 2) {
              piVar6 = (int *)*puVar18;
              *piVar6 = iVar14;
              piVar6[1] = iVar14 >> 0x1f;
            }
            else if (uVar4 == 3) {
              *(short *)*puVar18 = (short)iVar14;
            }
            else if (uVar4 == 4) {
              *(char *)*puVar18 = (char)iVar14;
            }
            else {
              *(int *)*puVar18 = iVar14;
            }
            param_2 = puVar18 + 1;
            goto LAB_0800d9ee;
          }
          if (uVar4 != 0x6f) goto LAB_0800d6f8;
          local_88 = (char *)0x8;
        }
        else {
          if (uVar4 == 0x73) {
            unaff_r10 = (char **)*puVar18;
            iVar5 = -1;
            goto LAB_0800d752;
          }
          if (uVar4 == 0x75) {
            local_88 = (char *)0xa;
          }
          else {
            if (uVar4 != 0x78) goto LAB_0800d6f8;
            local_88 = (char *)0x10;
          }
        }
LAB_0800d860:
        uVar12 = (uVar13 << 9) >> 0x1d;
        if (uVar12 == 2) {
          puVar10 = (uint *)((uint)((int)puVar18 + 7) & 0xfffffff8);
          param_2 = puVar10 + 2;
          uVar19 = *puVar10;
          uVar7 = puVar10[1];
        }
        else {
          param_2 = puVar18 + 1;
          uVar19 = *puVar18;
          uVar7 = 0;
          if (uVar12 == 3) {
            uVar19 = uVar19 & 0xffff;
          }
          if (uVar12 == 4) {
            uVar19 = uVar19 & 0xff;
          }
        }
        iVar5 = 0;
        if ((int)(uVar13 << 0x1c) < 0) {
          if (uVar4 == 0x70) {
            local_84 = (char *)CONCAT31(local_84._1_3_,0x40);
            iVar5 = 1;
          }
          else if ((local_88 == (char *)0x10) && (uVar19 != 0 || uVar7 != 0)) {
            local_84._0_2_ = CONCAT11(*param_1,0x30);
            iVar5 = 2;
          }
          if ((local_88 == (char *)0x8) &&
             ((uVar19 != 0 || uVar7 != 0 || ((int)(uVar13 << 0x1d) < 0)))) {
            local_84 = (char *)CONCAT31(local_84._1_3_,0x30);
            iVar5 = 1;
            pcVar16 = pcVar16 + -1;
          }
        }
LAB_0800d8ea:
        lVar24 = CONCAT44(uVar7,uVar19);
        if (uVar4 == 0x58) {
          local_7c = s_0123456789ABCDEF_0800d9d4;
        }
        else {
          local_7c = s_0123456789abcdef_0800d9c0;
        }
        local_80 = &local_50;
        while( true ) {
          if (lVar24 == 0) break;
          lVar24 = FUN_08005940((int)lVar24,(int)((ulonglong)lVar24 >> 0x20),local_88,0);
          local_80 = (char **)((int)local_80 + -1);
          *(char *)local_80 = local_7c[extraout_r2];
        }
        pcVar8 = (char *)((int)&local_50 - (int)local_80);
        if ((int)(uVar13 << 0x1d) < 0) {
          uVar13 = uVar13 & 0xfffeffff;
        }
        else {
          pcVar16 = (char *)0x1;
        }
        if ((int)pcVar8 < (int)pcVar16) {
          local_88 = pcVar16 + -(int)pcVar8;
        }
        else {
          local_88 = (char *)0x0;
        }
        local_74 = local_74 - (int)(pcVar8 + (int)(local_88 + iVar5));
        if (-1 < (int)(uVar13 << 0xf)) {
          iVar3 = FUN_0800dcc0(local_74,uVar13,local_2c,param_4);
          iVar14 = iVar14 + iVar3;
        }
        for (iVar3 = 0; iVar3 < iVar5; iVar3 = iVar3 + 1) {
          (*param_4)(*(undefined1 *)((int)&local_84 + iVar3),local_2c);
          iVar14 = iVar14 + 1;
        }
        if ((int)(uVar13 << 0xf) < 0) {
          iVar5 = FUN_0800dcc0(local_74,uVar13,local_2c,param_4);
          iVar14 = iVar14 + iVar5;
        }
        while (pcVar16 = local_88 + -1, bVar22 = 0 < (int)local_88, local_88 = pcVar16, bVar22) {
          (*param_4)(0x30,local_2c);
          iVar14 = iVar14 + 1;
        }
        while (unaff_r10 = (char **)(pcVar8 + -1), uVar4 = local_74, 0 < (int)pcVar8) {
          cVar2 = *(char *)local_80;
          local_80 = (char **)((int)local_80 + 1);
          (*param_4)(cVar2,local_2c);
          iVar14 = iVar14 + 1;
          pcVar8 = (char *)unaff_r10;
        }
        goto LAB_0800d9e8;
      }
      if (uVar4 == 0x58) {
        local_88 = (char *)0x10;
        goto LAB_0800d860;
      }
      if (0x58 < uVar4) {
        if (uVar4 == 99) {
          local_88._0_2_ = (ushort)(byte)*puVar18;
          iVar5 = 1;
          unaff_r10 = &local_88;
LAB_0800d752:
          param_2 = puVar18 + 1;
          iVar3 = 0;
          if ((int)(uVar13 << 0x1d) < 0) {
            for (; (iVar3 < (int)pcVar16 &&
                   ((iVar3 < iVar5 || (*(char *)((int)unaff_r10 + iVar3) != '\0'))));
                iVar3 = iVar3 + 1) {
            }
          }
          else {
            for (; (iVar3 < iVar5 || (*(char *)((int)unaff_r10 + iVar3) != '\0')); iVar3 = iVar3 + 1
                ) {
            }
          }
          uVar4 = local_74 - iVar3;
          iVar5 = FUN_0800dcc0(uVar4,uVar13,local_2c,param_4);
          iVar14 = iVar5 + iVar14 + iVar3;
          while (bVar22 = iVar3 != 0, iVar3 = iVar3 + -1, bVar22) {
            (*param_4)(*(char *)unaff_r10,local_2c);
            unaff_r10 = (char **)((int)unaff_r10 + 1);
          }
          goto LAB_0800d9e8;
        }
        if (uVar4 == 100) {
LAB_0800d7c2:
          local_88 = (char *)0xa;
          uVar12 = (uVar13 << 9) >> 0x1d;
          if (uVar12 == 2) {
            puVar10 = (uint *)((uint)((int)puVar18 + 7) & 0xfffffff8);
            param_2 = puVar10 + 2;
            uVar19 = *puVar10;
            uVar7 = puVar10[1];
          }
          else {
            param_2 = puVar18 + 1;
            uVar19 = *puVar18;
            if (uVar12 == 3) {
              uVar19 = (uint)(short)uVar19;
            }
            uVar7 = (int)uVar19 >> 0x1f;
            if (uVar12 == 4) {
              uVar19 = (uint)(char)uVar19;
              uVar7 = (int)uVar19 >> 0x1f;
            }
          }
          if ((int)uVar7 < 0) {
            bVar22 = uVar19 != 0;
            uVar19 = -uVar19;
            uVar7 = -(uint)bVar22 - uVar7;
            uVar9 = 0x2d;
LAB_0800d822:
            local_84 = (char *)CONCAT31(local_84._1_3_,uVar9);
            iVar5 = 1;
          }
          else {
            if ((int)(uVar13 << 0x14) < 0) {
              uVar9 = 0x2b;
              goto LAB_0800d822;
            }
            iVar5 = uVar13 << 0x1f;
            if (iVar5 != 0) {
              uVar9 = 0x20;
              goto LAB_0800d822;
            }
          }
          goto LAB_0800d8ea;
        }
        if (uVar4 != 0x65) goto LAB_0800d6f8;
        break;
      }
      if (uVar4 == 0) {
        return iVar14;
      }
      bVar23 = SBORROW4(uVar4,0x45);
      bVar21 = (int)(uVar4 - 0x45) < 0;
      bVar22 = uVar4 == 0x45;
      if (!bVar22) goto code_r0x0800d6ba;
    }
    goto LAB_0800da00;
  }
  goto LAB_0800d6f8;
code_r0x0800d6ba:
  bVar23 = SBORROW4(uVar4,0x46);
  bVar21 = (int)(uVar4 - 0x46) < 0;
  bVar22 = uVar4 == 0x46;
  if (!bVar22) goto code_r0x0800d6be;
  goto LAB_0800d6a8;
code_r0x0800d6be:
  if (uVar4 != 0x47) {
LAB_0800d6f8:
    (*param_4)(uVar4,local_2c);
    iVar14 = iVar14 + 1;
    goto LAB_0800d9ee;
  }
LAB_0800da00:
  if (-1 < (int)(uVar13 << 0x1d)) {
    pcVar16 = (char *)0x6;
  }
  puVar20 = (undefined4 *)((uint)((int)puVar18 + 7) & 0xfffffff8);
  param_2 = puVar20 + 2;
  uVar11 = *puVar20;
  if ((puVar20[1] & 0x80000000) == 0) {
    if ((int)(uVar13 << 0x14) < 0) {
      local_38 = &DAT_0800dc94;
    }
    else if ((uVar13 & 1) == 0) {
      local_38 = (byte *)(s_0123456789abcdef_0800d9c0 + 0x10);
    }
    else {
      local_38 = &DAT_0800dc98;
    }
  }
  else {
    local_38 = &DAT_0800dc90;
  }
  uVar12 = puVar20[1] & 0x7fffffff;
  if (uVar4 == 0x65) {
LAB_0800da6a:
    if ((int)pcVar16 < 0x11) {
      local_88 = pcVar16 + 1;
    }
    else {
      local_88 = (char *)0x11;
    }
    local_84 = (char *)0x0;
    FUN_0800d43c(&local_50,auStack_70,uVar11,uVar12);
    local_7c = pcStack_48;
    local_88 = local_50;
    unaff_r10 = (char **)(pcVar16 + 1);
    local_78 = (char **)0x0;
LAB_0800db32:
    local_78 = (char **)0x0;
    local_84 = (char *)0x1;
    local_80 = local_4c;
    local_88 = local_50;
    local_7c = pcStack_48;
  }
  else if (uVar4 < 0x66) {
    if (uVar4 == 0x45) goto LAB_0800da6a;
    if (uVar4 == 0x46) goto LAB_0800da96;
    if (uVar4 == 0x47) goto LAB_0800dadc;
  }
  else if (uVar4 == 0x66) {
LAB_0800da96:
    local_84 = (char *)0x1;
    local_80 = (char **)0x80000000;
    local_88 = pcVar16;
    FUN_0800d43c(&local_50,auStack_70,uVar11,uVar12);
    local_7c = pcStack_48;
    local_88 = local_50;
    local_78 = (char **)0x0;
    unaff_r10 = (char **)pcStack_48;
    if (local_44 == 0) {
      unaff_r10 = (char **)((int)local_4c + (int)(pcVar16 + 1));
    }
    iVar5 = (int)pcVar16 - (int)unaff_r10;
    if (-1 < iVar5) {
      unaff_r10 = (char **)(pcVar16 + 1);
      local_78 = (char **)(-1 - iVar5);
    }
    local_84 = (char *)((int)unaff_r10 + -(int)pcVar16);
  }
  else {
    if (uVar4 != 0x67) goto LAB_0800db66;
LAB_0800dadc:
    if ((int)pcVar16 < 1) {
      pcVar16 = (char *)0x1;
    }
    local_88 = pcVar16;
    if (0x11 < (int)pcVar16) {
      local_88 = (char *)0x11;
    }
    local_84 = (char *)0x0;
    FUN_0800d43c(&local_50,auStack_70,uVar11,uVar12);
    local_7c = pcStack_48;
    local_78 = (char **)0x0;
    local_88 = local_50;
    unaff_r10 = (char **)pcVar16;
    if (-1 < (int)(uVar13 << 0x1c)) {
      pcVar8 = pcStack_48;
      if ((int)pcVar16 <= (int)pcStack_48) goto LAB_0800db16;
      while( true ) {
        unaff_r10 = (char **)pcVar8;
LAB_0800db16:
        if (((int)unaff_r10 < 2) || (*(char *)((int)unaff_r10 + (int)(local_50 + -1)) != '0'))
        break;
        pcVar8 = (char *)((int)unaff_r10 + -1);
      }
    }
    if (((int)pcVar16 <= (int)local_4c) || ((int)(local_4c + 1) < 0 != SCARRY4((int)local_4c,4)))
    goto LAB_0800db32;
    if ((int)local_4c < 1) {
      local_78 = local_4c;
      pcVar16 = (char *)((int)unaff_r10 + -(int)local_4c);
LAB_0800db56:
      unaff_r10 = (char **)pcVar16;
    }
    else {
      pcVar16 = (char *)((int)local_4c + 1);
      if ((int)unaff_r10 < (int)pcVar16) goto LAB_0800db56;
    }
    local_84 = (char *)((int)local_4c + (1 - (int)local_78));
    local_80 = (char **)0x80000000;
  }
LAB_0800db66:
  if ((-1 < (int)(uVar13 << 0x1c)) && ((int)unaff_r10 <= (int)local_84)) {
    local_84 = (char *)0xffffffff;
  }
  local_3b[2] = 0;
  pbVar15 = local_3b + 2;
  if (local_80 != (char **)0x80000000) {
    local_50 = (char *)0x2b;
    iVar5 = 2;
    if ((int)local_80 < 0) {
      local_80 = (char **)-(int)local_80;
      local_50 = (char *)0x2d;
    }
    while ((0 < iVar5 || (local_80 != (char **)0x0))) {
      local_80 = (char **)FUN_08005914(local_80,10);
      pbVar15 = pbVar15 + -1;
      *pbVar15 = extraout_r1 + 0x30;
      iVar5 = iVar5 + -1;
    }
    pbVar15[-1] = (byte)local_50;
    pbVar15 = pbVar15 + -2;
    *pbVar15 = *param_1 & 0x20 | 0x45;
  }
  pbVar17 = local_3b + (2 - (int)pbVar15);
  uVar4 = (uint)*local_38;
  if (uVar4 != 0) {
    uVar4 = 1;
  }
  local_74 = (local_74 - (int)((int)unaff_r10 + (int)(pbVar17 + ((int)local_84 >> 0x1f) + uVar4))) -
             1;
  if (-1 < (int)(uVar13 << 0xf)) {
    iVar5 = FUN_0800dcc0(local_74,uVar13,local_2c,param_4);
    iVar14 = iVar14 + iVar5;
  }
  if (*local_38 != 0) {
    (*param_4)(*local_38,local_2c);
    iVar14 = iVar14 + 1;
  }
  iVar5 = iVar14;
  pcVar16 = (char *)unaff_r10;
  if ((int)(uVar13 << 0xf) < 0) {
    iVar5 = FUN_0800dcc0(local_74,uVar13,local_2c,param_4);
    iVar5 = iVar14 + iVar5;
  }
  while (iVar14 = iVar5, unaff_r10 = (char **)(pcVar16 + -1), 0 < (int)pcVar16) {
    if (((int)local_78 < 0) || ((int)local_7c <= (int)local_78)) {
      cVar2 = '0';
    }
    else {
      cVar2 = local_88[(int)local_78];
    }
    (*param_4)(cVar2,local_2c);
    local_78 = (char **)((int)local_78 + 1);
    local_84 = local_84 + -1;
    iVar5 = iVar14 + 1;
    pcVar16 = (char *)unaff_r10;
    if (local_84 == (char *)0x0) {
      (*param_4)(0x2e,local_2c);
      iVar5 = iVar14 + 2;
    }
  }
  while (uVar4 = local_74, 0 < (int)pbVar17) {
    (*param_4)(*pbVar15,local_2c);
    iVar14 = iVar14 + 1;
    pbVar15 = pbVar15 + 1;
    pbVar17 = pbVar17 + -1;
  }
LAB_0800d9e8:
  iVar5 = FUN_0800dc9c(uVar4,uVar13,local_2c,param_4);
  iVar14 = iVar14 + iVar5;
LAB_0800d9ee:
  param_1 = param_1 + 1;
  goto LAB_0800d9f0;
}


/* 0800dc9c FUN_0800dc9c */

int FUN_0800dc9c(int param_1,int param_2,undefined4 param_3,code *param_4)

{
  int iVar1;
  
  iVar1 = 0;
  if (param_2 << 0x12 < 0) {
    while (param_1 = param_1 + -1, -1 < param_1) {
      (*param_4)(0x20,param_3);
      iVar1 = iVar1 + 1;
    }
  }
  return iVar1;
}


/* 0800dcc0 FUN_0800dcc0 */

int FUN_0800dcc0(int param_1,int param_2,undefined4 param_3,code *param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = 0;
  if (param_2 << 0xf < 0) {
    uVar2 = 0x30;
  }
  else {
    uVar2 = 0x20;
  }
  if (-1 < param_2 << 0x12) {
    while (param_1 = param_1 + -1, -1 < param_1) {
      (*param_4)(uVar2,param_3);
      iVar1 = iVar1 + 1;
    }
  }
  return iVar1;
}


/* 0800dcee FUN_0800dcee */

void FUN_0800dcee(undefined4 param_1)

{
  switch(param_1) {
  default:
    FUN_08012d70();
    FUN_08012d5c();
    break;
  case 1:
    FUN_08012db8();
    FUN_08012d70();
    break;
  case 2:
  case 3:
    FUN_08012da0();
    FUN_08012d70();
    break;
  case 4:
  case 5:
  case 6:
    FUN_08012db8();
    FUN_08012d8c();
  }
  return;
}


/* 0800dd4a FUN_0800dd4a */

void FUN_0800dd4a(undefined1 param_1,undefined4 *param_2)

{
  undefined1 *puVar1;
  
  puVar1 = (undefined1 *)*param_2;
  *param_2 = puVar1 + 1;
  *puVar1 = param_1;
  return;
}


/* 0800dd54 FUN_0800dd54 */

void FUN_0800dd54(int param_1)

{
  int *piVar1;
  int iVar2;
  uint in_fpscr;
  undefined4 uVar3;
  
  for (iVar2 = 0; piVar1 = DAT_0800de64, iVar2 < 3; iVar2 = iVar2 + 1) {
    if (*DAT_0800de50 == 0x14) {
      FUN_0800f478(DAT_0800de54 + iVar2 * 0x14);
    }
    uVar3 = VectorSignedToFloat((int)*(short *)(param_1 + iVar2 * 2),(byte)(in_fpscr >> 0x15) & 3);
    FUN_0800f480(uVar3,DAT_0800de54 + iVar2 * 0x14);
    if (*DAT_0800de50 == 1) {
      uVar3 = FUN_0800f4f0(DAT_0800de54 + iVar2 * 0x14);
      *(undefined4 *)(DAT_0800de58 + iVar2 * 4) = uVar3;
    }
  }
  if (*DAT_0800de50 == 1) {
    for (iVar2 = 0; iVar2 < 3; iVar2 = iVar2 + 1) {
      if ((DAT_0800de5c < *(float *)(DAT_0800de58 + iVar2 * 4)) ||
         (*(float *)(DAT_0800de58 + iVar2 * 4) == 0.0)) {
        if (*(float *)(DAT_0800de58 + iVar2 * 4) <= DAT_0800de60) {
          *DAT_0800de64 = 0;
        }
        else {
          *DAT_0800de64 = *DAT_0800de64 + 1;
          if (1 < *piVar1) {
            *DAT_0800de68 = 1;
          }
        }
        break;
      }
    }
    if (2 < iVar2) {
      *DAT_0800de68 = 0;
    }
    *DAT_0800de50 = 0x14;
  }
  else {
    *DAT_0800de50 = *DAT_0800de50 + -1;
  }
  return;
}


/* 0800de6c FUN_0800de6c */

undefined4 FUN_0800de6c(void)

{
  return *DAT_0800de74;
}


/* 0800de78 FUN_0800de78 */

void FUN_0800de78(void)

{
  undefined4 *puVar1;
  
  puVar1 = DAT_0800de84;
  DAT_0800de84[1] = 0;
  *puVar1 = 0;
  puVar1[2] = 0;
  return;
}


/* 0800de88 FUN_0800de88 */

int FUN_0800de88(void)

{
  int *piVar1;
  
  piVar1 = DAT_0800deb0;
  DAT_0800deb0[2] =
       (int)(((ulonglong)(uint)(*DAT_0800deb0 * 0x65) / 0x28) / (ulonglong)(uint)DAT_0800deb0[1]);
  *piVar1 = 0;
  piVar1[1] = 0;
  return piVar1[2];
}


/* 0800deb4 FUN_0800deb4 */

undefined4 FUN_0800deb4(void)

{
  return *(undefined4 *)(DAT_0800debc + 8);
}


/* 0800dec0 FUN_0800dec0 */

undefined2 FUN_0800dec0(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_0800df14(param_1);
  if ((param_1 == 1) || (param_1 == 3)) {
    *(short *)(DAT_0800df10 + param_1 * 2) = (short)(((uint)(iVar1 * 0xc91) >> 0xc) * 0xb00 >> 8);
  }
  else {
    *(short *)(DAT_0800df10 + param_1 * 2) = (short)((uint)(iVar1 * 0xc910) >> 0x10);
  }
  return *(undefined2 *)(DAT_0800df10 + param_1 * 2);
}


/* 0800df14 FUN_0800df14 */

uint FUN_0800df14(int param_1)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  if ((param_1 == 3) || (param_1 == 4)) {
    uVar2 = FUN_0800cd04(*(undefined1 *)(DAT_0800df5c + param_1));
  }
  else {
    for (iVar1 = 0; iVar1 < 0x14; iVar1 = iVar1 + 1) {
      uVar2 = uVar2 + *(ushort *)(DAT_0800df60 + iVar1 * 6 + param_1 * 2);
    }
    uVar2 = uVar2 / 0x14 & 0xffff;
  }
  return uVar2;
}


/* 0800df64 FUN_0800df64 */

void FUN_0800df64(void)

{
  int iVar1;
  undefined1 local_54;
  undefined1 local_53;
  undefined1 local_52;
  undefined1 local_51;
  int local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined1 local_24;
  undefined1 local_23;
  undefined4 local_20;
  undefined4 local_1c;
  undefined1 local_18;
  undefined2 local_14 [4];
  undefined4 local_c;
  
  FUN_0800a294(4,1);
  FUN_0800a254(0x1000);
  FUN_0800a254(1);
  FUN_08005cae(0,2);
  FUN_080098b8(local_14);
  local_14[0] = 0x3e;
  local_c = 3;
  FUN_080096d0(DAT_0800e0dc,local_14);
  FUN_0800939c(DAT_0800e0e0);
  local_50 = DAT_0800e0e4;
  local_4c = DAT_0800e0e8;
  local_48 = 0;
  local_44 = 0x3c;
  local_40 = 0;
  local_3c = 0x80;
  local_38 = 0x100;
  local_34 = 0x400;
  local_30 = 0x20;
  local_2c = 0x3000;
  local_28 = 0;
  FUN_080094cc(DAT_0800e0e0,&local_50);
  FUN_08009508(0,DAT_0800e0e0 + -8,DAT_0800e0e0,1);
  FUN_08009388(DAT_0800e0e0,2,1);
  local_54 = 0xb;
  local_53 = 0;
  local_52 = 1;
  local_51 = 1;
  FUN_0800a180(&local_54);
  FUN_08009484(DAT_0800e0e0,1);
  FUN_08005e58(DAT_0800e0e4 + -0x4c);
  local_24 = 1;
  local_23 = 1;
  local_20 = 0xe0000;
  local_1c = 0;
  local_18 = 3;
  FUN_08005f2c(DAT_0800e0e4 + -0x4c,&local_24);
  FUN_08005d92(DAT_0800e0e4 + -0x4c,3,1,6);
  FUN_08005d92(DAT_0800e0e4 + -0x4c,5,2,6);
  FUN_08005d92(DAT_0800e0e4 + -0x4c,6,3);
  FUN_08005e8e(DAT_0800e0e4 + -0x4c,1);
  FUN_08005d7a(DAT_0800e0e4 + -0x4c,1);
  FUN_08005ce8(DAT_0800e0e4 + -0x4c,4,1,7);
  FUN_08005cd8(DAT_0800e0e4 + -0x4c,0x7000);
  FUN_08005e78(DAT_0800e0e4 + -0x4c,1);
  do {
    iVar1 = FUN_08005efc(DAT_0800e0e4 + -0x4c,0x20);
  } while (iVar1 == 0);
  FUN_08005f78(DAT_0800e0e4 + -0x4c);
  do {
    iVar1 = FUN_08005ed0(DAT_0800e0e4 + -0x4c);
  } while (iVar1 != 0);
  FUN_08005ea4(DAT_0800e0e4 + -0x4c,1);
  return;
}


/* 0800e0ec FUN_0800e0ec */

uint FUN_0800e0ec(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_0800f448(DAT_0800e138,0x82,param_1);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = (int)(((uint)*(ushort *)(DAT_0800e138 + (iVar1 + -1) * 2) - param_1) * 10) /
            (int)((uint)*(ushort *)(DAT_0800e138 + (iVar1 + -1) * 2) -
                 (uint)*(ushort *)(DAT_0800e138 + iVar1 * 2)) + (iVar1 + -0x1f) * 10 & 0xffff;
  }
  return uVar2;
}


/* 0800e13c FUN_0800e13c */

int FUN_0800e13c(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = param_1;
  if (param_1 < 1) {
    iVar1 = -param_1;
  }
  if (iVar1 < param_2) {
    param_1 = 0;
  }
  else if (param_1 < 1) {
    if (param_1 < 0) {
      param_1 = param_1 + param_2;
    }
  }
  else {
    param_1 = param_1 - param_2;
  }
  return param_1;
}


/* 0800e15e FUN_0800e15e */

uint FUN_0800e15e(int param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = 0;
  for (uVar1 = 0; uVar1 < param_2; uVar1 = uVar1 + 1) {
    uVar2 = uVar2 + *(ushort *)(param_1 + uVar1 * 2);
  }
  return uVar2 / param_2 & 0xffff;
}


/* 0800e17c FUN_0800e17c */

void FUN_0800e17c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  uStack_10 = param_3;
  uStack_c = param_4;
  for (iVar1 = 0; iVar1 < 6; iVar1 = iVar1 + 1) {
    if ((*(byte *)(DAT_0800e1a8 + 0x1c) & 8) == 0) {
      FUN_08012c54(&uStack_10);
      FUN_0800dd54(&uStack_10);
      FUN_0800d2bc(&uStack_10);
    }
  }
  return;
}


/* 0800e1ac FUN_0800e1ac */

void FUN_0800e1ac(void)

{
  FUN_0800e1d8();
  *DAT_0800e1c8 = 0;
  *DAT_0800e1cc = 0;
  *DAT_0800e1d0 = 0;
  *DAT_0800e1d4 = 0;
  return;
}


/* 0800e1d8 FUN_0800e1d8 */

void FUN_0800e1d8(void)

{
  FUN_0800e1f4(0);
  return;
}


/* 0800e1e4 FUN_0800e1e4 */

void FUN_0800e1e4(void)

{
  FUN_0800e1f4(*DAT_0800e1f0);
  return;
}


/* 0800e1f4 FUN_0800e1f4 */

undefined8 FUN_0800e1f4(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined2 local_20;
  undefined2 local_1e;
  undefined2 local_1c;
  undefined2 local_1a;
  undefined4 local_18;
  undefined4 local_14;
  
  local_1c = (undefined2)param_2;
  local_1a = (undefined2)((uint)param_2 >> 0x10);
  local_20 = (undefined2)param_1;
  local_1e = (undefined2)((uint)param_1 >> 0x10);
  local_18 = param_3;
  local_14 = param_4;
  FUN_0800a918(&local_20);
  if (param_1 < 1) {
    FUN_0800a804(DAT_0800e274,0x50);
  }
  else {
    uVar1 = (param_1 * *DAT_0800e278) / 100;
    if (*DAT_0800e278 < uVar1) {
      uVar1 = *DAT_0800e278;
    }
    FUN_0800a918(&local_20);
    local_20 = 0x70;
    local_1e = 1;
    local_1c = 4;
    local_1a = (undefined2)uVar1;
    local_18 = 0;
    local_14 = 0x1000100;
    FUN_0800a8a4(DAT_0800e274,&local_20);
    FUN_0800a84c(DAT_0800e274,1);
    FUN_0800a862(DAT_0800e274,1);
  }
  return CONCAT26(local_1a,CONCAT24(local_1c,CONCAT22(local_1e,local_20)));
}


/* 0800e27c FUN_0800e27c */

void FUN_0800e27c(uint param_1)

{
  byte *pbVar1;
  uint uVar2;
  byte *pbVar3;
  
  if (param_1 == 0) {
    FUN_0800e1ac();
  }
  else {
    for (uVar2 = 0; pbVar3 = (byte *)0x0, uVar2 < 5; uVar2 = uVar2 + 1) {
      pbVar1 = (byte *)(DAT_0800e2d4 + uVar2 * 8);
      if (*pbVar1 == param_1) {
        pbVar3 = pbVar1;
        if ((*DAT_0800e2d8 != 0) && (pbVar3 = (byte *)0x0, pbVar1[1] < *(byte *)(*DAT_0800e2d8 + 1))
           ) {
          pbVar3 = pbVar1;
        }
        break;
      }
    }
    if (pbVar3 != (byte *)0x0) {
      *DAT_0800e2d8 = (int)pbVar3;
      *DAT_0800e2dc = 0;
      *DAT_0800e2e0 = 0;
    }
  }
  return;
}


/* 0800e2e4 FUN_0800e2e4 */

void FUN_0800e2e4(void)

{
  uint uVar1;
  int iVar2;
  
  if ((*DAT_0800e390 != 0) && (uVar1 = FUN_08011fa8(), *DAT_0800e394 <= uVar1)) {
    if (*DAT_0800e398 == '\0') {
      *DAT_0800e398 = '\x01';
      if (*(char *)(*(int *)(*DAT_0800e390 + 4) + (uint)*DAT_0800e39c) != '\0') {
        FUN_0800e1e4();
      }
    }
    else {
      *DAT_0800e398 = '\0';
      if (*(char *)(*(int *)(*DAT_0800e390 + 4) + (uint)*DAT_0800e39c) != '\0') {
        FUN_0800e1d8();
      }
    }
    if (*(char *)(*(int *)(*DAT_0800e390 + 4) + (uint)*DAT_0800e39c) == -2) {
      *DAT_0800e39c = 0;
    }
    else if (*(char *)(*(int *)(*DAT_0800e390 + 4) + (uint)*DAT_0800e39c) == -1) {
      FUN_0800e1ac();
    }
    else {
      iVar2 = FUN_08011fa8();
      *DAT_0800e394 =
           (short)(ushort)*(byte *)(*(int *)(*DAT_0800e390 + 4) + (uint)*DAT_0800e39c) * 10 + iVar2;
      *DAT_0800e39c = *DAT_0800e39c + 1;
    }
  }
  return;
}


/* 0800e3a0 FUN_0800e3a0 */

void FUN_0800e3a0(void)

{
  uint *puVar1;
  undefined2 local_34;
  undefined2 local_32;
  undefined2 local_30;
  undefined2 local_2e;
  undefined2 local_2c;
  undefined2 local_2a;
  undefined2 local_28;
  undefined2 local_26;
  undefined2 local_24;
  undefined2 local_22;
  undefined2 local_20;
  undefined2 local_1e;
  undefined1 local_1c;
  undefined2 local_14;
  undefined1 local_12;
  undefined4 local_c;
  undefined4 local_8;
  
  FUN_0800a2b4(0x800);
  FUN_0800a2b4(5,1);
  FUN_080098b8(&local_14);
  local_14 = 0x80;
  local_c = 2;
  local_12 = 0x11;
  local_8 = 5;
  FUN_080096d0(DAT_0800e480,&local_14);
  FUN_0800a92c(&local_24);
  puVar1 = DAT_0800e488;
  *DAT_0800e488 = *DAT_0800e484 / 0xa8c;
  local_20 = (undefined2)*puVar1;
  local_24 = 0;
  local_1e = 0;
  local_22 = 0;
  local_1c = 0;
  FUN_0800a94c(DAT_0800e48c,&local_24);
  FUN_0800a7ee(DAT_0800e48c,1);
  FUN_0800a918(&local_34);
  local_34 = 0x60;
  local_32 = 1;
  local_30 = 4;
  local_2e = 0;
  local_2c = 0;
  local_2a = 0;
  local_28 = 0x100;
  local_26 = 0;
  FUN_0800a8a4(DAT_0800e48c,&local_34);
  FUN_0800a83a(DAT_0800e48c,8);
  FUN_0800a828(DAT_0800e48c,4);
  FUN_0800a804(DAT_0800e48c,0x50);
  FUN_0800a84c(DAT_0800e48c,1);
  FUN_0800a862(DAT_0800e48c,1);
  return;
}


/* 0800e490 FUN_0800e490 */

/* WARNING: Removing unreachable block (ram,0x0800e4f4) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0800e490(void)

{
  undefined4 in_r3;
  undefined4 local_10;
  
  local_10 = in_r3;
  FUN_0800a5f8(4);
  *DAT_0800e530 = *DAT_0800e528 / DAT_0800e52c;
  if (*DAT_0800e528 / 1000 - 1 < 0x1000000) {
    _DAT_e000e014 = *DAT_0800e528 / 1000 - 1;
    FUN_0800adbc(0xffffffff,0xf);
    _DAT_e000e018 = 0;
    _DAT_e000e010 = 7;
    FUN_0800adbc(0xffffffff);
    local_10 = 0x10000ff;
    FUN_0800a180(&local_10);
    return;
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}


/* 0800e534 FUN_0800e534 */

undefined4 FUN_0800e534(int param_1)

{
  uint uVar1;
  ushort uVar2;
  short sVar3;
  
  for (uVar1 = 0; uVar1 < (*(byte *)(param_1 + 0x20) & 7); uVar1 = uVar1 + 1 & 0xff) {
    if (*(uint *)(param_1 + 4 + uVar1 * 4) >> 0x1e == 0) {
      uVar2 = (ushort)((uint)(*(int *)(param_1 + 4 + uVar1 * 4) << 0xc) >> 0x16) * 0x32;
      sVar3 = (*(ushort *)(param_1 + 4 + uVar1 * 4) & 0x3ff) * 10;
      FUN_0800f808(4,s_driver_pd_0800e79c,s____src_drivers_src_DriverPD_c_0800e77c,DAT_0800e778,0x57
                   ,s_PDO__d_fixed_voltage___d_current_0800e74c,uVar1,uVar2,sVar3);
      if (*(ushort *)(param_1 + 0x28) < uVar2) {
        *(ushort *)(param_1 + 0x28) = uVar2;
        *(short *)(param_1 + 0x2a) = sVar3;
      }
    }
    else if (*(uint *)(param_1 + 4 + uVar1 * 4) >> 0x1e == 1) {
      FUN_0800f808(4,s_driver_pd_0800e79c,s____src_drivers_src_DriverPD_c_0800e77c,DAT_0800e778,100,
                   s_PDO__d_battery_voltageMax___d_vo_0800e7a8,uVar1,
                   (short)(ushort)((uint)(*(int *)(param_1 + 4 + uVar1 * 4) << 2) >> 0x16) * 0x32,
                   (short)(ushort)((uint)(*(int *)(param_1 + 4 + uVar1 * 4) << 0xc) >> 0x16) * 0x32,
                   (short)(ushort)(((uint)*(ushort *)(param_1 + 4 + uVar1 * 4) << 0x16) >> 0x16) *
                   0xfa);
    }
    else if (*(uint *)(param_1 + 4 + uVar1 * 4) >> 0x1e == 2) {
      FUN_0800f808(4,s_driver_pd_0800e79c,s____src_drivers_src_DriverPD_c_0800e77c,DAT_0800e778,0x6c
                   ,DAT_0800e7e8,uVar1,
                   (short)(ushort)((uint)(*(int *)(param_1 + 4 + uVar1 * 4) << 2) >> 0x16) * 0x32,
                   (short)(ushort)((uint)(*(int *)(param_1 + 4 + uVar1 * 4) << 0xc) >> 0x16) * 0x32,
                   (*(ushort *)(param_1 + 4 + uVar1 * 4) & 0x3ff) * 10);
    }
    else if ((uint)(*(int *)(param_1 + 4 + uVar1 * 4) << 2) >> 0x1e == 0) {
      FUN_0800f808(4,s_driver_pd_0800e79c,s____src_drivers_src_DriverPD_c_0800e77c,DAT_0800e778,0x74
                   ,DAT_0800e7ec,uVar1,
                   (short)(ushort)(byte)((uint)(*(int *)(param_1 + 4 + uVar1 * 4) << 7) >> 0x18) *
                   100,(short)(*(ushort *)(param_1 + 4 + uVar1 * 4) >> 8) * 100,
                   (short)(*(byte *)(param_1 + 4 + uVar1 * 4) & 0x7f) * 0x32);
    }
    else if ((uint)(*(int *)(param_1 + 4 + uVar1 * 4) << 2) >> 0x1e == 1) {
      FUN_0800f808(4,s_driver_pd_0800e79c,s____src_drivers_src_DriverPD_c_0800e77c,DAT_0800e778,0x7c
                   ,s_PDO__d_EPR_voltageMax___d_voltag_0800e7f0,uVar1,
                   (short)(ushort)((uint)(*(int *)(param_1 + 4 + uVar1 * 4) << 6) >> 0x17) * 100,
                   (short)(*(ushort *)(param_1 + 4 + uVar1 * 4) >> 8) * 100,
                   (short)(ushort)*(byte *)(param_1 + 4 + uVar1 * 4) * 0x32);
    }
    else if ((uint)(*(int *)(param_1 + 4 + uVar1 * 4) << 2) >> 0x1e == 2) {
      FUN_0800f808(4,s_driver_pd_0800e79c,s____src_drivers_src_DriverPD_c_0800e77c,DAT_0800e778,0x80
                   ,s_PDO__d_SPR_0800e82c,uVar1);
    }
    else {
      FUN_0800f808(4,s_driver_pd_0800e79c,s____src_drivers_src_DriverPD_c_0800e77c,DAT_0800e778,0x84
                   ,s_SPR_error__0800e83c);
    }
  }
  return 0;
}


/* 0800e84c FUN_0800e84c */

undefined4 FUN_0800e84c(ushort *param_1)

{
  undefined4 *puVar1;
  byte bVar2;
  undefined4 uVar3;
  
  puVar1 = DAT_0800eb08;
  if (param_1 == (ushort *)0x0) {
    uVar3 = 1;
  }
  else {
    if (-1 < (short)*param_1) {
      if (((uint)*param_1 << 0x11) >> 0x1d == 0) {
        FUN_0800f808(4,s_driver_pd_0800eb3c,s____src_drivers_src_DriverPD_c_0800eb1c,DAT_0800eb18,
                     0xbe,&DAT_0800eb0c);
        switch((byte)*param_1 & 0x1f) {
        case 2:
          FUN_0800f808(4,s_driver_pd_0800eb3c,s____src_drivers_src_DriverPD_c_0800eb1c,DAT_0800eb18,
                       0xc3,s_DEF_TYPE_GOTOMIN_0800eb48);
          break;
        case 3:
          FUN_0800f808(4,s_driver_pd_0800eb3c,s____src_drivers_src_DriverPD_c_0800eb1c,DAT_0800eb18,
                       200,&DAT_0800eb5c);
          break;
        case 4:
          FUN_0800f808(4,s_driver_pd_0800eb3c,s____src_drivers_src_DriverPD_c_0800eb1c,DAT_0800eb18,
                       0xce,s_DEF_TYPE_REJECT_0800eb7c);
          break;
        case 6:
          FUN_0800f808(4,s_driver_pd_0800eb3c,s____src_drivers_src_DriverPD_c_0800eb1c,DAT_0800eb18,
                       0xd3,&DAT_0800eb90);
          break;
        case 7:
          FUN_0800f808(4,s_driver_pd_0800eb3c,s____src_drivers_src_DriverPD_c_0800eb1c,DAT_0800eb18,
                       0xdc,s_DEF_TYPE_GET_SRC_CAP_0800ebb0);
          break;
        case 8:
          FUN_0800f808(4,s_driver_pd_0800eb3c,s____src_drivers_src_DriverPD_c_0800eb1c,DAT_0800eb18,
                       0xe3,s_DEF_TYPE_GET_SNK_CAP_0800ebc8);
          break;
        case 9:
          FUN_0800f808(4,s_driver_pd_0800eb3c,s____src_drivers_src_DriverPD_c_0800eb1c,DAT_0800eb18,
                       0xe9,s_DEF_TYPE_DR_SWAP_0800ebe0);
          break;
        case 10:
          FUN_0800f808(4,s_driver_pd_0800eb3c,s____src_drivers_src_DriverPD_c_0800eb1c,DAT_0800eb18,
                       0xef,s_DEF_TYPE_PR_SWAP_0800ebf4);
          break;
        case 0xb:
          FUN_0800f808(4,s_driver_pd_0800eb3c,s____src_drivers_src_DriverPD_c_0800eb1c,DAT_0800eb18,
                       0xf5,s_DEF_TYPE_VCONN_SWAP_0800ec08);
          break;
        case 0xc:
          FUN_0800f808(4,s_driver_pd_0800eb3c,s____src_drivers_src_DriverPD_c_0800eb1c,DAT_0800eb18,
                       0xfb,s_DEF_TYPE_WAIT_0800ec20);
          break;
        case 0xd:
          FUN_0800f808(4,s_driver_pd_0800eb3c,s____src_drivers_src_DriverPD_c_0800eb1c,DAT_0800eb18,
                       0x100,s_DEF_TYPE_SOFT_RESET_0800ec30);
          break;
        case 0xe:
          FUN_0800f808(4,s_driver_pd_0800eb3c,s____src_drivers_src_DriverPD_c_0800eb1c,DAT_0800eb18,
                       0x107,s_DEF_TYPE_DATA_RESET_0800ec48);
          break;
        case 0xf:
          FUN_0800f808(4,s_driver_pd_0800eb3c,s____src_drivers_src_DriverPD_c_0800eb1c,DAT_0800eb18,
                       0x10c,s_DEF_TYPE_DATA_RESET_CMP_0800ec60);
          break;
        case 0x10:
          FUN_0800f808(4,s_driver_pd_0800eb3c,s____src_drivers_src_DriverPD_c_0800eb1c,DAT_0800eb18,
                       0x111,s_DEF_TYPE_NOT_SUPPORT_0800ec7c);
          break;
        case 0x11:
          FUN_0800f808(4,s_driver_pd_0800eb3c,s____src_drivers_src_DriverPD_c_0800eb1c,DAT_0800eb18,
                       0x116,s_DEF_TYPE_GET_SRC_CAP_EX_0800ec94);
          break;
        case 0x12:
          FUN_0800f808(4,s_driver_pd_0800eb3c,s____src_drivers_src_DriverPD_c_0800eb1c,DAT_0800eb18,
                       0x11b,s_DEF_TYPE_GET_STATUS_0800ecb0);
          break;
        case 0x14:
          FUN_0800f808(4,s_driver_pd_0800eb3c,s____src_drivers_src_DriverPD_c_0800eb1c,DAT_0800eb18,
                       0x120,s_DEF_TYPE_GET_PPS_STATUS_0800ecc8);
          break;
        case 0x15:
          FUN_0800f808(4,s_driver_pd_0800eb3c,s____src_drivers_src_DriverPD_c_0800eb1c,DAT_0800eb18,
                       0x125,s_DEF_TYPE_GET_CTY_CODES_0800ece4);
        }
      }
      else {
        FUN_0800f808(4,s_driver_pd_0800eb3c,s____src_drivers_src_DriverPD_c_0800eb1c,DAT_0800eb18,
                     0x12f,&DAT_0800ed00);
        bVar2 = (byte)*param_1 & 0x1f;
        if (bVar2 == 1) {
          FUN_080053ee(puVar1 + 1,param_1 + 1,(((uint)*param_1 << 0x11) >> 0x1d) << 2);
          *(byte *)(puVar1 + 8) = *(byte *)(puVar1 + 8) & 0xf8 | (byte)(*param_1 >> 0xc) & 7;
          FUN_0800f808(4,s_driver_pd_0800eb3c,s____src_drivers_src_DriverPD_c_0800eb1c,DAT_0800eb18,
                       0x138,&DAT_0800ed0c);
          FUN_0800e534(puVar1);
        }
        else if (bVar2 == 2) {
          FUN_0800f808(4,s_driver_pd_0800eb3c,s____src_drivers_src_DriverPD_c_0800eb1c,DAT_0800eb18,
                       0x13f,s_DEF_TYPE_REQUEST_0800ed20);
        }
        else if ((bVar2 != 10) && (bVar2 == 0xf)) {
          *puVar1 = *(undefined4 *)(param_1 + 9);
          FUN_0800f808(4,s_driver_pd_0800eb3c,s____src_drivers_src_DriverPD_c_0800eb1c,DAT_0800eb18,
                       0x149,&DAT_0800ed34);
          FUN_0800ed4c(puVar1);
        }
      }
    }
    uVar3 = 0;
  }
  return uVar3;
}


/* 0800ed4c FUN_0800ed4c */

longlong FUN_0800ed4c(uint param_1)

{
  return (ulonglong)param_1 << 0x20;
}


/* 0800ed54 FUN_0800ed54 */

undefined4 FUN_0800ed54(void)

{
  return DAT_0800ed58;
}


/* 0800ed5c FUN_0800ed5c */

char FUN_0800ed5c(char *param_1,uint param_2)

{
  uint uVar1;
  char cVar2;
  
  cVar2 = '\0';
  for (uVar1 = 0; uVar1 < param_2; uVar1 = uVar1 + 1) {
    cVar2 = *param_1 + cVar2;
    param_1 = param_1 + 1;
  }
  return cVar2;
}


/* 0800ed78 FUN_0800ed78 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0800ed78(void)

{
  ushort uVar1;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  undefined1 auStack_50 [52];
  
  if (((DAT_0800ee80[6] == '\0') && (*DAT_0800ee80 != '\0')) && (*DAT_0800ee80 != -1)) {
    uVar3 = FUN_08010a6c(0x22,9);
    if ((uVar3 & 0x10) == 0) {
      if (((uVar3 & 8) != 0) &&
         (uVar1 = *DAT_0800eed4, *DAT_0800eed4 = uVar1 + 1, 0x28 < (ushort)(uVar1 + 1))) {
        FUN_08010a0e(0x22,0x60,0x30,auStack_50);
        FUN_0800f628(&DAT_0800eed8,0x10,auStack_50,0x2f);
        FUN_0800e84c(auStack_50);
        iVar4 = FUN_0800ed54();
        pcVar2 = DAT_0800ee80;
        *(undefined2 *)(DAT_0800ee80 + 4) = *(undefined2 *)(iVar4 + 0x2a);
        *(undefined2 *)(pcVar2 + 2) = *(undefined2 *)(iVar4 + 0x28);
        iVar4 = FUN_08011fa8();
        FUN_0800f808(3,s_ch224q_0800eecc,s____src_drivers_src_ch224q_c_0800eeb0,DAT_0800eeac,0xc6,
                     s_PD3_0_ready_vol__d__da_time__d_0800eedc,*(ushort *)(DAT_0800ee80 + 2) / 1000,
                     *(ushort *)(DAT_0800ee80 + 4) / 1000,iVar4 - *_DAT_0800ee88);
        DAT_0800ee80[6] = '\x01';
      }
    }
    else {
      uVar1 = *DAT_0800ee84;
      *DAT_0800ee84 = uVar1 + 1;
      if (0x1e < (ushort)(uVar1 + 1)) {
        pcVar2 = DAT_0800ee80;
        pcVar2[4] = -0x78;
        pcVar2[5] = '\x13';
        pcVar2[2] = '`';
        pcVar2[3] = 'm';
        iVar4 = FUN_08011fa8();
        FUN_0800f808(3,s_ch224q_0800eecc,s____src_drivers_src_ch224q_c_0800eeb0,DAT_0800eeac,0xb4,
                     s_PD3_1_ready_vol_28_5a_time__d_0800ee8b + 1,iVar4 - *_DAT_0800ee88);
        DAT_0800ee80[6] = '\x01';
      }
    }
  }
  return;
}


/* 0800eefc FUN_0800eefc */

undefined4 FUN_0800eefc(void)

{
  return DAT_0800ef00;
}


/* 0800ef04 FUN_0800ef04 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_0800ef04(undefined4 param_1,undefined4 param_2)

{
  byte *pbVar1;
  byte bVar2;
  undefined4 uVar3;
  
  bVar2 = FUN_08010a6c(0x22,9);
  pbVar1 = _DAT_0800ef90;
  *_DAT_0800ef90 = bVar2;
  if ((*pbVar1 == 0) || (*pbVar1 == 0xff)) {
    uVar3 = 0xffffffff;
  }
  else {
    param_2 = 0x44;
    FUN_0800f808(3,s_ch224q_0800efc8,s____src_drivers_src_ch224q_c_0800efac,DAT_0800efa8,0x44,
                 s_ch224_info_sta__X_0800ef93 + 1,*_DAT_0800ef90);
    if ((*_DAT_0800ef90 & 8) == 0) {
      FUN_0800d3ac(4);
    }
    else {
      FUN_0800d3ac(5);
      _DAT_0800ef90[7] = 1;
    }
    uVar3 = FUN_08011fa8();
    *DAT_0800efd0 = uVar3;
    FUN_08005ffa(DAT_0800efd4,1);
    FUN_08005ffa(DAT_0800efd4,2);
    FUN_08005ffa(DAT_0800efd8,0x200);
    FUN_08005ffa(DAT_0800efd8,0x100);
    uVar3 = 0;
  }
  return CONCAT44(param_2,uVar3);
}


/* 0800efdc FUN_0800efdc */

void FUN_0800efdc(int param_1)

{
  ushort uVar1;
  int iVar2;
  
  iVar2 = FUN_0801246c();
  if (iVar2 == 0) {
    return;
  }
  if (param_1 == 6) {
    uVar1 = *(ushort *)(DAT_0800f044 + 2);
    if (uVar1 == 15000) {
      param_1 = 3;
    }
    else {
      if (uVar1 < 0x3a99) {
        if (uVar1 == 9000) {
          param_1 = 1;
          goto LAB_0800f03a;
        }
        if (uVar1 == 12000) {
          param_1 = 2;
          goto LAB_0800f03a;
        }
      }
      else {
        if (uVar1 == 20000) {
          param_1 = 4;
          goto LAB_0800f03a;
        }
        if (uVar1 == 28000) {
          param_1 = 5;
          goto LAB_0800f03a;
        }
      }
      param_1 = 0;
    }
  }
LAB_0800f03a:
  FUN_0800d3ac(param_1);
  return;
}


/* 0800f048 FUN_0800f048 */

undefined4 FUN_0800f048(ushort *param_1,ushort *param_2)

{
  undefined4 uVar1;
  
  if (*param_2 < *param_1) {
    uVar1 = 0xffffffff;
  }
  else if (*param_1 < *param_2) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}


/* 0800f070 FUN_0800f070 */

void FUN_0800f070(void)

{
  FUN_080053ee(*DAT_0800f088,DAT_0800f084,0x70);
  FUN_0800f08c();
  return;
}


/* 0800f08c FUN_0800f08c */

void FUN_0800f08c(void)

{
  int iVar1;
  
  iVar1 = FUN_0800ed5c(*DAT_0800f0b8 + 4,0x6c);
  if (*(int *)*DAT_0800f0b8 != iVar1) {
    *(int *)*DAT_0800f0b8 = iVar1;
    FUN_08010230(DAT_0800f0c0,DAT_0800f0bc,0x28);
  }
  return;
}


/* 0800f0c4 FUN_0800f0c4 */

undefined1 FUN_0800f0c4(void)

{
  return *(undefined1 *)(*DAT_0800f0cc + 2);
}


/* 0800f0d0 FUN_0800f0d0 */

uint FUN_0800f0d0(void)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = *(int *)(*DAT_0800f148 + 0x30 + (uint)*(byte *)(*DAT_0800f148 + 0x2c) * 4) * 100;
  if (*(char *)(*DAT_0800f148 + 0x2c) == '\0') {
    iVar1 = FUN_0801246c();
    if (iVar1 == 0) {
      iVar1 = FUN_08012b54();
      if (iVar1 == 0) {
        uVar2 = 3000;
      }
      else {
        iVar1 = FUN_08012b4c();
        uVar2 = (uint)*(ushort *)(iVar1 + 2);
      }
    }
    else {
      iVar1 = FUN_0800eefc();
      uVar2 = (uint)*(ushort *)(iVar1 + 4);
    }
    if ((*(char *)(*DAT_0800f14c + 0x20) == '\0') &&
       (iVar1 = FUN_0800f154(),
       uVar2 * iVar1 - DAT_0800f150 != 0 && DAT_0800f150 <= (int)(uVar2 * iVar1))) {
      iVar1 = FUN_08010ce8();
      if (iVar1 == 0) {
        uVar2 = 0xcb2;
      }
      else {
        uVar2 = DAT_0800f150 / (int)(uint)*(ushort *)*DAT_0800f14c;
      }
    }
  }
  return uVar2;
}


/* 0800f154 FUN_0800f154 */

uint FUN_0800f154(void)

{
  byte bVar1;
  int iVar2;
  ushort *puVar3;
  uint uVar4;
  uint uVar5;
  undefined4 local_18;
  undefined4 uStack_14;
  
  local_18 = DAT_0800f1c0;
  uStack_14 = DAT_0800f1c4;
  bVar1 = FUN_08012480();
  uVar4 = (uint)bVar1;
  uVar5 = (short)(ushort)*(byte *)((int)&local_18 + uVar4) * 1000;
  iVar2 = FUN_0801246c();
  if (iVar2 == 0) {
    iVar2 = FUN_08012b54();
    if ((iVar2 != 0) && ((uVar4 == 6 || (3 < uVar4)))) {
      puVar3 = (ushort *)FUN_08012b4c();
      uVar5 = (uint)*puVar3;
    }
  }
  else if ((uVar4 == 6) || (uVar4 == 5)) {
    iVar2 = FUN_0800eefc();
    uVar5 = (uint)*(ushort *)(iVar2 + 2);
    if ((*(char *)(*DAT_0800f1c8 + 0x20) == '\0') && (20000 < uVar5)) {
      uVar5 = 20000;
    }
  }
  iVar2 = FUN_08010ce8();
  if (iVar2 != 0) {
    uVar5 = (uint)*(ushort *)*DAT_0800f1c8;
  }
  return uVar5;
}


/* 0800f1cc FUN_0800f1cc */

void FUN_0800f1cc(int param_1)

{
  if ((*(char *)(*DAT_0800f1fc + 2) == '\0') || (param_1 == 0)) {
    *(char *)(*DAT_0800f1fc + 2) = (char)param_1;
    FUN_08012720(*DAT_0800f1fc + 0xc,param_1);
    FUN_08012720(*DAT_0800f1fc + 100,param_1);
  }
  return;
}


/* 0800f200 FUN_0800f200 */

void FUN_0800f200(int param_1)

{
  if ((param_1 == 1) || (param_1 == 3)) {
    FUN_0800f1cc(1);
  }
  else {
    FUN_0800f1cc(0);
  }
  *(char *)(*DAT_0800f22c + 0x2a) = (char)param_1;
  return;
}


/* 0800f230 FUN_0800f230 */

void FUN_0800f230(void)

{
  *(undefined1 *)(*DAT_0800f23c + 0x34) = 1;
  return;
}


/* 0800f240 FUN_0800f240 */

void FUN_0800f240(int param_1)

{
  undefined2 uVar1;
  
  if ((*(char *)(*DAT_0800f26c + 0x20) == '\0') && (param_1 == 6)) {
    param_1 = 4;
  }
  FUN_0800efdc(param_1);
  FUN_08012b68(param_1);
  uVar1 = FUN_0800f154();
  *(undefined2 *)(*DAT_0800f26c + 0x3c) = uVar1;
  return;
}


/* 0800f270 FUN_0800f270 */

void FUN_0800f270(int param_1)

{
  uint in_fpscr;
  undefined4 uVar1;
  
  if (*(int *)(*DAT_0800f2a8 + 0x24) < param_1) {
    *(undefined1 *)(*DAT_0800f2a8 + 0x2b) = 1;
  }
  else {
    *(undefined1 *)(*DAT_0800f2a8 + 0x2b) = 3;
  }
  uVar1 = VectorSignedToFloat(param_1,(byte)(in_fpscr >> 0x15) & 3);
  *(undefined4 *)(*DAT_0800f2ac + 0xb8) = uVar1;
  *(int *)(*DAT_0800f2a8 + 0x38) = param_1;
  return;
}


/* 0800f2b0 FUN_0800f2b0 */

void FUN_0800f2b0(void)

{
  undefined2 uVar1;
  undefined4 uVar2;
  int iVar3;
  float fVar4;
  
  if (*(int *)(*DAT_0800f39c + 0x10) == 0) {
    uVar2 = 10;
  }
  else {
    uVar2 = *(undefined4 *)(*DAT_0800f39c + 0x10);
  }
  FUN_0800ade4(uVar2);
  FUN_0800f200(0);
  *(undefined1 *)(*DAT_0800f3a0 + 0x29) = 1;
  *(undefined4 *)(*DAT_0800f3a0 + 0x24) = 0x50;
  uVar1 = FUN_0800dec0(3);
  *(undefined2 *)*DAT_0800f3a0 = uVar1;
  uVar1 = FUN_0800dec0(0);
  *(undefined2 *)(*DAT_0800f3a0 + 2) = uVar1;
  uVar1 = FUN_0800dec0(1);
  *(undefined2 *)(*DAT_0800f3a0 + 6) = uVar1;
  FUN_0800df14(0);
  fVar4 = (float)FUN_08012450();
  *(char *)(*DAT_0800f3a0 + 8) = (char)(int)fVar4;
  uVar1 = FUN_0800dec0(4);
  *(undefined2 *)(*DAT_0800f3a0 + 4) = uVar1;
  *(undefined4 *)(*DAT_0800f3a0 + 0x1c) = 0;
  if (*(ushort *)(*DAT_0800f3a0 + 4) < 0xc59) {
    *(undefined1 *)(*DAT_0800f3a8 + 0xd4) = 1;
  }
  else {
    *(uint *)(DAT_0800f3a4 + 0x1c) = *(uint *)(DAT_0800f3a4 + 0x1c) | 1;
  }
  iVar3 = FUN_08012b98();
  if (iVar3 == 0) {
    *(uint *)(DAT_0800f3a4 + 0x1c) = *(uint *)(DAT_0800f3a4 + 0x1c) | 8;
    *(undefined1 *)(*DAT_0800f3a0 + 0x29) = 0;
  }
  FUN_0800c3b0(*(undefined2 *)(*DAT_0800f3a0 + 2));
  FUN_0800c380(*(undefined2 *)(*DAT_0800f3a0 + 6),*(undefined2 *)*DAT_0800f3a0);
  FUN_0800ce8c();
  return;
}


/* 0800f3ac FUN_0800f3ac */

void FUN_0800f3ac(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)(DAT_0800f40c + param_1 * 0xc);
  FUN_080128b4(*puVar1,puVar1[1],puVar1[2],*DAT_0800f410 + 0xc);
  puVar1 = (undefined4 *)(DAT_0800f414 + param_1 * 0xc);
  FUN_080128b4(*puVar1,puVar1[1],puVar1[2],*DAT_0800f410 + 100);
  return;
}


/* 0800f418 FUN_0800f418 */

void FUN_0800f418(int param_1)

{
  bool bVar1;
  
  while (bVar1 = param_1 != 0, param_1 = param_1 + -1, bVar1) {
    FUN_0800f430(1000);
  }
  return;
}


/* 0800f430 FUN_0800f430 */

void FUN_0800f430(uint param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_08011edc();
  do {
    iVar2 = FUN_08011edc();
  } while ((uint)(iVar2 - iVar1) < param_1);
  return;
}


/* 0800f448 FUN_0800f448 */

int FUN_0800f448(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = 0;
  iVar4 = param_2 + -1;
  iVar1 = param_2 + -1;
  while (iVar3 <= iVar4) {
    iVar2 = iVar3 + (iVar4 - iVar3) / 2;
    if (param_3 < (int)(uint)*(ushort *)(param_1 + iVar2 * 2)) {
      iVar3 = iVar2 + 1;
    }
    else {
      iVar4 = iVar2 + -1;
      iVar1 = iVar2;
    }
  }
  return iVar1;
}


/* 0800f478 FUN_0800f478 */

void FUN_0800f478(int param_1)

{
  *(undefined4 *)(param_1 + 0x10) = 0;
  return;
}


/* 0800f480 FUN_0800f480 */

void FUN_0800f480(float param_1,float *param_2)

{
  uint in_fpscr;
  float fVar1;
  
  param_2[4] = (float)((int)param_2[4] + 1);
  if (param_2[4] == 1.4013e-45) {
    param_2[1] = param_1;
    *param_2 = param_1;
    param_2[2] = DAT_0800f4ec;
  }
  else {
    fVar1 = (float)VectorSignedToFloat(param_2[4],(byte)(in_fpscr >> 0x15) & 3);
    param_2[1] = (param_1 - *param_2) / fVar1 + *param_2;
    param_2[3] = param_2[2] + (param_1 - *param_2) * (param_1 - param_2[1]);
    *param_2 = param_2[1];
    param_2[2] = param_2[3];
  }
  return;
}


/* 0800f4f0 FUN_0800f4f0 */

float FUN_0800f4f0(int param_1)

{
  uint in_fpscr;
  float fVar1;
  
  fVar1 = DAT_0800f514;
  if (1 < *(int *)(param_1 + 0x10)) {
    fVar1 = (float)VectorSignedToFloat(*(int *)(param_1 + 0x10) + -1,(byte)(in_fpscr >> 0x15) & 3);
    fVar1 = *(float *)(param_1 + 0xc) / fVar1;
  }
  return fVar1;
}


/* 0800f518 FUN_0800f518 */

undefined1 FUN_0800f518(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined1 uVar3;
  
  if (param_1 == 0) {
    if (*DAT_0800f5bc == 0) {
      FUN_0800f808(0,&DAT_0800f61c,s____lib_easylogger_src_elog_c_0800f5fc,DAT_0800f5c0,0x1ab,
                   s___s__has_assert_failed_at__s__ld_0800f5d8,s_tag______void___0__0800f5c4,
                   DAT_0800f5c0,0x1ab);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    (*(code *)*DAT_0800f5bc)(s_tag______void___0__0800f5c4,DAT_0800f5c0,0x1ab);
  }
  uVar3 = 5;
  if (*(char *)(DAT_0800f624 + 0xf0) == '\0') {
    uVar3 = 5;
  }
  else {
    FUN_0800fcc4();
    for (uVar2 = 0; uVar2 < 5; uVar2 = uVar2 + 1 & 0xff) {
      if ((*(char *)(DAT_0800f624 + uVar2 * 0x21 + 0x51) == '\x01') &&
         (iVar1 = FUN_080054ac(param_1,DAT_0800f624 + uVar2 * 0x21 + 0x32,0x1e), iVar1 == 0)) {
        uVar3 = *(undefined1 *)(DAT_0800f624 + 0x31 + uVar2 * 0x21);
        break;
      }
    }
    FUN_0800fc50();
  }
  return uVar3;
}


/* 0800f628 FUN_0800f628 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_0800f628(uint param_1,int param_2,int param_3,int param_4)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint local_38;
  int iStack_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  local_30 = 0;
  local_2c = 0;
  local_38 = param_1;
  iStack_34 = param_2;
  if (((_DAT_0800f780[0xf1] != 0) && (3 < *_DAT_0800f780)) &&
     (iVar2 = FUN_0800544e(param_1,_DAT_0800f780 + 1), iVar2 != 0)) {
    FUN_0800fbe8();
    uVar3 = 0;
    local_38 = param_1;
    while (uVar4 = uVar3, (int)uVar4 < param_4) {
      iStack_34 = uVar4 + param_2 + -1;
      uVar3 = FUN_0800ad08(DAT_0800f79c,0x200,s_D_HEX__s___04X__04X__0800f783 + 1,param_1);
      if (((int)uVar3 < 0) || (0x200 < (int)uVar3)) {
        uVar3 = 0x200;
      }
      else {
        uVar3 = uVar3 & 0xffff;
      }
      for (uVar5 = 0; (int)uVar5 < param_2; uVar5 = uVar5 + 1 & 0xffff) {
        if ((int)(uVar4 + uVar5) < param_4) {
          FUN_0800ad08(&local_30,8,s__02X_0800f7a0,*(undefined1 *)(param_3 + uVar4 + uVar5));
        }
        else {
          FUN_08005472(&local_30,&DAT_0800f7a8,8);
        }
        iVar2 = FUN_0800ffe4(uVar3,DAT_0800f79c + uVar3,&local_30);
        uVar3 = iVar2 + uVar3 & 0xffff;
        if (uVar5 + 1 == ((int)(uVar5 + 1) >> 3) * 8) {
          iVar2 = FUN_0800ffe4(uVar3,DAT_0800f79c + uVar3,s_D_HEX__s___04X__04X__0800f783 + 0x15);
          uVar3 = iVar2 + uVar3 & 0xffff;
        }
      }
      iVar2 = FUN_0800ffe4(uVar3,DAT_0800f79c + uVar3,&DAT_0800f7ac);
      uVar3 = iVar2 + uVar3 & 0xffff;
      for (uVar5 = 0; (int)uVar5 < param_2; uVar5 = uVar5 + 1 & 0xffff) {
        if ((int)(uVar4 + uVar5) < param_4) {
          if (*(byte *)(param_3 + uVar4 + uVar5) - 0x20 < 0x5f) {
            uVar1 = *(undefined1 *)(param_3 + uVar4 + uVar5);
          }
          else {
            uVar1 = 0x2e;
          }
          FUN_0800ad08(&local_30,8,&DAT_0800f7b0,uVar1);
          iVar2 = FUN_0800ffe4(uVar3,DAT_0800f79c + uVar3,&local_30);
          uVar3 = iVar2 + uVar3 & 0xffff;
        }
      }
      if (0x200 < uVar3 + 2) {
        uVar3 = 0x1fe;
      }
      iVar2 = FUN_0800ffe4(uVar3,DAT_0800f79c + uVar3,&DAT_0800f7b4);
      FUN_0800fca8(DAT_0800f79c,iVar2 + uVar3 & 0xffff);
      local_38 = uVar4;
      uVar3 = uVar4 + param_2 & 0xffff;
    }
    FUN_0800fc50();
  }
  return CONCAT44(iStack_34,local_38);
}


/* 0800f7b8 FUN_0800f7b8 */

int FUN_0800f7b8(void)

{
  int iVar1;
  int iVar2;
  
  if (*(char *)(DAT_0800f804 + 0xf0) == '\x01') {
    iVar2 = 0;
  }
  else {
    iVar2 = FUN_0800fca4();
    if (iVar2 == 0) {
      FUN_0800fc10(1);
      iVar1 = DAT_0800f804;
      *(undefined1 *)(DAT_0800f804 + 0xf3) = 0;
      *(undefined1 *)(iVar1 + 0xf4) = 0;
      FUN_0800ff58();
      FUN_0800fcc8(5);
      FUN_0800fd88();
      *(undefined1 *)(DAT_0800f804 + 0xf0) = 1;
    }
  }
  return iVar2;
}


/* 0800f808 FUN_0800f808 */

void FUN_0800f808(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  
  uVar1 = FUN_0800549e(param_2);
  iVar4 = 0;
  local_2c = 0;
  local_28 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  if (5 < param_1) {
    if (*DAT_0800fb3c == 0) {
      FUN_0800f808(0,&DAT_0800fba4,s____lib_easylogger_src_elog_c_0800fb84,DAT_0800fb40,0x209,
                   s___s__has_assert_failed_at__s__ld_0800fb60,s_level_<__ELOG_LVL_VERBOSE_0800fb44,
                   DAT_0800fb40,0x209);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    (*(code *)*DAT_0800fb3c)(s_level_<__ELOG_LVL_VERBOSE_0800fb44,DAT_0800fb40,0x209);
  }
  if ((((DAT_0800fbac[0xf1] != 0) && (param_1 <= (int)(uint)*DAT_0800fbac)) &&
      (iVar2 = FUN_0800f518(param_2), param_1 <= iVar2)) &&
     (iVar2 = FUN_0800544e(param_2,DAT_0800fbac + 1), iVar2 != 0)) {
    FUN_0800fbe8();
    if (DAT_0800fbac[0xf5] != 0) {
      iVar4 = FUN_0800ffe4(0,DAT_0800fbb0,&DAT_0800fbb4);
      iVar2 = FUN_0800ffe4(iVar4,DAT_0800fbb0 + iVar4,*(undefined4 *)(DAT_0800fbb8 + param_1 * 4));
      iVar4 = iVar4 + iVar2;
    }
    iVar2 = FUN_08010418(param_1,1);
    if (iVar2 != 0) {
      iVar2 = FUN_0800ffe4(iVar4,DAT_0800fbb0 + iVar4,*(undefined4 *)(DAT_0800fbbc + param_1 * 4));
      iVar4 = iVar4 + iVar2;
    }
    iVar2 = FUN_08010418(param_1,2);
    if (iVar2 != 0) {
      iVar2 = FUN_0800ffe4(iVar4,DAT_0800fbb0 + iVar4,param_2);
      iVar4 = iVar4 + iVar2;
      if (uVar1 < 0x10) {
        FUN_08005412(&local_3c,0xf - uVar1,0x20);
        iVar2 = FUN_0800ffe4(iVar4,DAT_0800fbb0 + iVar4,&local_3c);
        iVar4 = iVar4 + iVar2;
      }
      iVar2 = FUN_0800ffe4(iVar4,DAT_0800fbb0 + iVar4,&DAT_0800fbc0);
      iVar4 = iVar4 + iVar2;
    }
    iVar2 = FUN_08010418(param_1,0x1c);
    if (iVar2 != 0) {
      iVar2 = FUN_0800ffe4(iVar4,DAT_0800fbb0 + iVar4,&DAT_0800fbc4);
      iVar4 = iVar4 + iVar2;
      iVar2 = FUN_08010418(param_1,4);
      if (iVar2 != 0) {
        uVar3 = FUN_0800fc94();
        iVar2 = FUN_0800ffe4(iVar4,DAT_0800fbb0 + iVar4,uVar3);
        iVar4 = iVar4 + iVar2;
        iVar2 = FUN_08010418(param_1,0x18);
        if (iVar2 != 0) {
          iVar2 = FUN_0800ffe4(iVar4,DAT_0800fbb0 + iVar4,&DAT_0800fbc0);
          iVar4 = iVar4 + iVar2;
        }
      }
      iVar2 = FUN_08010418(param_1,8);
      if (iVar2 != 0) {
        uVar3 = FUN_0800fc78();
        iVar2 = FUN_0800ffe4(iVar4,DAT_0800fbb0 + iVar4,uVar3);
        iVar4 = iVar4 + iVar2;
        iVar2 = FUN_08010418(param_1,0x10);
        if (iVar2 != 0) {
          iVar2 = FUN_0800ffe4(iVar4,DAT_0800fbb0 + iVar4,&DAT_0800fbc0);
          iVar4 = iVar4 + iVar2;
        }
      }
      iVar2 = FUN_08010418(param_1,0x10);
      if (iVar2 != 0) {
        uVar3 = FUN_0800fc84();
        iVar2 = FUN_0800ffe4(iVar4,DAT_0800fbb0 + iVar4,uVar3);
        iVar4 = iVar4 + iVar2;
      }
      iVar2 = FUN_0800ffe4(iVar4,DAT_0800fbb0 + iVar4,&DAT_0800fbc8);
      iVar4 = iVar4 + iVar2;
    }
    iVar2 = FUN_08010418(param_1,0xe0);
    if (iVar2 != 0) {
      iVar2 = FUN_0800ffe4(iVar4,DAT_0800fbb0 + iVar4,&DAT_0800fbcc);
      iVar4 = iVar4 + iVar2;
      iVar2 = FUN_08010418(param_1,0x20);
      if (iVar2 != 0) {
        iVar2 = FUN_0800ffe4(iVar4,DAT_0800fbb0 + iVar4,param_3);
        iVar4 = iVar4 + iVar2;
        iVar2 = FUN_08010418(param_1,0x40);
        if (iVar2 == 0) {
          iVar2 = FUN_08010418(param_1,0x80);
          if (iVar2 != 0) {
            iVar2 = FUN_0800ffe4(iVar4,DAT_0800fbb0 + iVar4,&DAT_0800fbd0);
            iVar4 = iVar4 + iVar2;
          }
        }
        else {
          iVar2 = FUN_0800ffe4(iVar4,DAT_0800fbb0 + iVar4,&DAT_0800fbc0);
          iVar4 = iVar4 + iVar2;
        }
      }
      iVar2 = FUN_08010418(param_1,0x40);
      if (iVar2 != 0) {
        iVar2 = FUN_0800ffe4(iVar4,DAT_0800fbb0 + iVar4,param_4);
        iVar4 = iVar4 + iVar2;
        iVar2 = FUN_08010418(param_1,0x80);
        if (iVar2 != 0) {
          iVar2 = FUN_0800ffe4(iVar4,DAT_0800fbb0 + iVar4,&DAT_0800fbd0);
          iVar4 = iVar4 + iVar2;
        }
      }
      iVar2 = FUN_08010418(param_1,0x80);
      if (iVar2 != 0) {
        FUN_0800ad08(&local_2c,5,&DAT_0800fbd4,param_5);
        iVar2 = FUN_0800ffe4(iVar4,DAT_0800fbb0 + iVar4,&local_2c);
        iVar4 = iVar4 + iVar2;
      }
      iVar2 = FUN_0800ffe4(iVar4,DAT_0800fbb0 + iVar4,&DAT_0800fbd8);
      iVar4 = iVar4 + iVar2;
    }
    iVar2 = FUN_0800ad60(DAT_0800fbb0 + iVar4,0x200 - iVar4,param_6,&stack0x00000008);
    if (((uint)(iVar4 + iVar2) < 0x201) && (-1 < iVar2)) {
      iVar4 = iVar4 + iVar2;
    }
    else {
      iVar4 = 0x200;
    }
    if (0x200 < iVar4 + 6U) {
      iVar4 = 0x1fa;
    }
    if (DAT_0800fbac[0x20] != 0) {
      *(undefined1 *)(DAT_0800fbb0 + iVar4) = 0;
      iVar2 = FUN_0800544e(DAT_0800fbb0,DAT_0800fbac + 0x20);
      if (iVar2 == 0) {
        FUN_0800fc50();
        return;
      }
    }
    if (DAT_0800fbac[0xf5] != 0) {
      iVar2 = FUN_0800ffe4(iVar4,DAT_0800fbb0 + iVar4,&DAT_0800fbdc);
      iVar4 = iVar4 + iVar2;
    }
    iVar2 = FUN_0800ffe4(iVar4,DAT_0800fbb0 + iVar4,&DAT_0800fbe4);
    FUN_0800fca8(DAT_0800fbb0,iVar4 + iVar2);
    FUN_0800fc50();
  }
  return;
}


/* 0800fbe8 FUN_0800fbe8 */

void FUN_0800fbe8(void)

{
  if (*(char *)(DAT_0800fc0c + 0xf2) == '\0') {
    *(undefined1 *)(DAT_0800fc0c + 0xf3) = 1;
  }
  else {
    FUN_0800fcc4();
    *(undefined1 *)(DAT_0800fc0c + 0xf4) = 1;
  }
  return;
}


/* 0800fc10 FUN_0800fc10 */

void FUN_0800fc10(undefined1 param_1)

{
  int iVar1;
  
  iVar1 = DAT_0800fc4c;
  *(undefined1 *)(DAT_0800fc4c + 0xf2) = param_1;
  if (*(char *)(iVar1 + 0xf2) != '\0') {
    if ((*(char *)(DAT_0800fc4c + 0xf4) == '\0') && (*(char *)(DAT_0800fc4c + 0xf3) != '\0')) {
      FUN_0800fcc4();
    }
    else if ((*(char *)(DAT_0800fc4c + 0xf4) != '\0') && (*(char *)(DAT_0800fc4c + 0xf3) == '\0')) {
      FUN_0800fcc6();
    }
  }
  return;
}


/* 0800fc50 FUN_0800fc50 */

void FUN_0800fc50(void)

{
  if (*(char *)(DAT_0800fc74 + 0xf2) == '\0') {
    *(undefined1 *)(DAT_0800fc74 + 0xf3) = 0;
  }
  else {
    FUN_0800fcc6();
    *(undefined1 *)(DAT_0800fc74 + 0xf4) = 0;
  }
  return;
}


/* 0800fc78 FUN_0800fc78 */

undefined * FUN_0800fc78(void)

{
  return &DAT_0800fc7c;
}


/* 0800fc84 FUN_0800fc84 */

char * FUN_0800fc84(void)

{
  return s_thread_0_0800fc88;
}


/* 0800fc94 FUN_0800fc94 */

char * FUN_0800fc94(void)

{
  return s_Sep_17_2025_0800fc98;
}


/* 0800fca4 FUN_0800fca4 */

undefined4 FUN_0800fca4(void)

{
  return 0;
}


/* 0800fca8 FUN_0800fca8 */

void FUN_0800fca8(undefined4 param_1,undefined4 param_2)

{
  FUN_0800ace8(&DAT_0800fcbc,param_2,param_1);
  return;
}


/* 0800fcc4 FUN_0800fcc4 */

void FUN_0800fcc4(void)

{
  return;
}


/* 0800fcc6 FUN_0800fcc6 */

void FUN_0800fcc6(void)

{
  return;
}


/* 0800fcc8 FUN_0800fcc8 */

void FUN_0800fcc8(int param_1)

{
  if (5 < param_1) {
    if (*DAT_0800fd14 == 0) {
      FUN_0800f808(0,&DAT_0800fd7c,s____lib_easylogger_src_elog_c_0800fd5c,DAT_0800fd18,0x125,
                   s___s__has_assert_failed_at__s__ld_0800fd38,s_level_<__ELOG_LVL_VERBOSE_0800fd1c,
                   DAT_0800fd18,0x125);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    (*(code *)*DAT_0800fd14)(s_level_<__ELOG_LVL_VERBOSE_0800fd1c,DAT_0800fd18,0x125);
  }
  *DAT_0800fd84 = (char)param_1;
  return;
}


/* 0800fd88 FUN_0800fd88 */

void FUN_0800fd88(void)

{
  int iVar1;
  uint uVar2;
  
  for (uVar2 = 0; uVar2 < 5; uVar2 = uVar2 + 1 & 0xff) {
    FUN_08005420(DAT_0800fdc0 + uVar2 * 0x21 + 1,0x1f);
    iVar1 = DAT_0800fdc0;
    *(undefined1 *)(DAT_0800fdc0 + uVar2 * 0x21) = 0;
    *(undefined1 *)(iVar1 + uVar2 * 0x21 + 0x20) = 0;
  }
  return;
}


/* 0800fdc4 FUN_0800fdc4 */

void FUN_0800fdc4(int param_1,undefined4 param_2)

{
  if (5 < param_1) {
    if (*DAT_0800fe14 == 0) {
      FUN_0800f808(0,&DAT_0800fe7c,s____lib_easylogger_src_elog_c_0800fe5c,DAT_0800fe18,0x10b,
                   s___s__has_assert_failed_at__s__ld_0800fe38,s_level_<__ELOG_LVL_VERBOSE_0800fe1c,
                   DAT_0800fe18,0x10b);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    (*(code *)*DAT_0800fe14)(s_level_<__ELOG_LVL_VERBOSE_0800fe1c,DAT_0800fe18,0x10b);
  }
  *(undefined4 *)(DAT_0800fe84 + param_1 * 4) = param_2;
  return;
}


/* 0800fe88 FUN_0800fe88 */

void FUN_0800fe88(int param_1)

{
  if ((param_1 != 0) && (param_1 != 1)) {
    if (*DAT_0800fed8 == 0) {
      FUN_0800f808(0,&DAT_0800ff4c,s____lib_easylogger_src_elog_c_0800ff2c,DAT_0800fedc,0xe2,
                   s___s__has_assert_failed_at__s__ld_0800ff08,
                   s__enabled____false______enabled___0800fee0,DAT_0800fedc,0xe2);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    (*(code *)*DAT_0800fed8)(s__enabled____false______enabled___0800fee0,DAT_0800fedc,0xe2);
  }
  *(char *)(DAT_0800ff54 + 0xf1) = (char)param_1;
  return;
}


/* 0800ff58 FUN_0800ff58 */

void FUN_0800ff58(undefined1 param_1)

{
  *(undefined1 *)(DAT_0800ff60 + 0xf5) = param_1;
  return;
}


/* 0800ff64 FUN_0800ff64 */

void FUN_0800ff64(void)

{
  FUN_0800fe88(1);
  FUN_0800f808(3,&DAT_0800ffdc,s____lib_easylogger_src_elog_c_0800ffbc,DAT_0800ffb8,0xd9,
               s_EasyLogger_V_s_is_initialize_suc_0800ff90,s_2_2_99_0800ff88);
  return;
}


/* 0800ffe4 FUN_0800ffe4 */

int FUN_0800ffe4(uint param_1,char *param_2,char *param_3)

{
  char *pcVar1;
  
  if (param_2 == (char *)0x0) {
    if (*DAT_08010088 == 0) {
      FUN_0800f808(0,&DAT_080100dc,s____lib_easylogger_src_elog_utils_080100b8,DAT_0801008c,0x2c,
                   s___s__has_assert_failed_at__s__ld_08010094,&DAT_08010090,DAT_0801008c,0x2c);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    (*(code *)*DAT_08010088)(&DAT_08010090,DAT_0801008c,0x2c);
  }
  pcVar1 = param_3;
  if (param_3 == (char *)0x0) {
    if (*DAT_08010088 == 0) {
      FUN_0800f808(0,&DAT_080100dc,s____lib_easylogger_src_elog_utils_080100b8,DAT_0801008c,0x2d,
                   s___s__has_assert_failed_at__s__ld_08010094,&DAT_080100e4,DAT_0801008c,0x2d);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    (*(code *)*DAT_08010088)(&DAT_080100e4,DAT_0801008c,0x2d);
  }
  while ((*pcVar1 != '\0' && (param_1 < 0x200))) {
    *param_2 = *pcVar1;
    pcVar1 = pcVar1 + 1;
    param_2 = param_2 + 1;
    param_1 = param_1 + 1;
  }
  return (int)pcVar1 - (int)param_3;
}


/* 080100e8 FUN_080100e8 */

ulonglong FUN_080100e8(undefined4 param_1,undefined4 param_2)

{
  return CONCAT44(param_2,param_1) & 0x7fffffffffffffff;
}


/* 08010100 FUN_08010100 */

void FUN_08010100(undefined4 *param_1,int param_2,uint param_3)

{
  uint uVar1;
  
  for (uVar1 = 0; uVar1 < param_3; uVar1 = uVar1 + 1 & 0xffff) {
    *(undefined4 *)(param_2 + uVar1 * 4) = *param_1;
    param_1 = param_1 + 1;
  }
  return;
}


/* 0801011a FUN_0801011a */

undefined4 FUN_0801011a(int param_1,int *param_2,uint param_3)

{
  undefined4 uVar1;
  uint uVar2;
  int *piVar3;
  
  if (param_3 < 0x201) {
    piVar3 = param_2;
    for (uVar2 = 0; uVar2 < 0x200 / param_3; uVar2 = uVar2 + 1) {
      piVar3 = (int *)(param_1 * 0x800 + 0x8000000 + uVar2 * param_3 * 4);
      if (*piVar3 == -1) {
        if (uVar2 != 0) {
          piVar3 = (int *)(param_1 * 0x800 + 0x8000000 + (uVar2 - 1) * param_3 * 4);
        }
        break;
      }
    }
    for (uVar2 = 0; uVar2 < param_3; uVar2 = uVar2 + 1) {
      param_2[uVar2] = *piVar3;
      piVar3 = piVar3 + 1;
    }
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}


/* 0801017e FUN_0801017e */

undefined4 FUN_0801017e(int param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int unaff_r6;
  
  if (param_3 < 0x201) {
    for (uVar4 = 0; uVar4 < 0x200 / param_3; uVar4 = uVar4 + 1) {
      unaff_r6 = param_1 * 0x800 + 0x8000000 + uVar4 * param_3 * 4;
      for (uVar2 = 0; (uVar2 < param_3 && (*(int *)(unaff_r6 + uVar2 * 4) == -1)); uVar2 = uVar2 + 1
          ) {
      }
      if (param_3 <= uVar2) break;
      if ((uVar2 < param_3) && (0x200 / param_3 - 1 == uVar4)) {
        unaff_r6 = param_1 * 0x800 + 0x8000000;
      }
    }
    FUN_08009690();
    FUN_08009524(0x34);
    if ((param_1 * 0x800 + 0x8000000 == unaff_r6) && (iVar3 = FUN_08009580(unaff_r6), iVar3 != 6)) {
      uVar1 = 0;
    }
    else {
      for (uVar4 = 0; uVar4 < param_3; uVar4 = uVar4 + 1) {
        iVar3 = FUN_08009638(unaff_r6,*(undefined4 *)(param_2 + uVar4 * 4));
        if (iVar3 != 6) {
          return 0;
        }
        unaff_r6 = unaff_r6 + 4;
      }
      FUN_08009624();
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}


/* 08010230 FUN_08010230 */

void FUN_08010230(int param_1,int param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  FUN_08009690();
  FUN_08009524(0x34);
  uVar3 = param_1 + 0xf8000000U >> 0xb;
  uVar4 = (uint)(param_1 << 0x15) >> 0x17;
  uVar1 = 0x200 - uVar4;
  if (param_3 <= 0x200 - uVar4) {
    uVar1 = param_3;
  }
  while( true ) {
    FUN_08010100(uVar3 * 0x800 + 0x8000000,DAT_080102fc,0x200);
    uVar2 = 0;
    while ((uVar2 < uVar1 && (*(int *)(DAT_080102fc + (uVar4 + uVar2) * 4) == -1))) {
      uVar2 = uVar2 + 1;
    }
    if (uVar2 < uVar1) {
      FUN_08009580(uVar3 * 0x800 + 0x8000000);
      for (uVar2 = 0; uVar2 < uVar1; uVar2 = uVar2 + 1) {
        *(undefined4 *)(DAT_080102fc + (uVar2 + uVar4) * 4) = *(undefined4 *)(param_2 + uVar2 * 4);
      }
      FUN_08010300(uVar3 * 0x800 + 0x8000000,DAT_080102fc,0x200);
    }
    else {
      FUN_08010300(param_1,param_2,uVar1);
    }
    if (param_3 == uVar1) break;
    uVar3 = uVar3 + 1;
    uVar4 = 0;
    param_2 = param_2 + uVar1 * 4;
    param_1 = param_1 + uVar1 * 4;
    param_3 = param_3 - uVar1;
    uVar1 = param_3;
    if (0x200 < param_3) {
      uVar1 = 0x200;
    }
  }
  FUN_08009624();
  return;
}


/* 08010300 FUN_08010300 */

void FUN_08010300(int param_1,int param_2,uint param_3)

{
  uint uVar1;
  
  for (uVar1 = 0; uVar1 < param_3; uVar1 = uVar1 + 1) {
    FUN_08009638(param_1,*(undefined4 *)(param_2 + uVar1 * 4));
    param_1 = param_1 + 4;
  }
  return;
}


/* 08010324 FUN_08010324 */

int FUN_08010324(byte *param_1,ushort *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  if (*(int *)(param_2 + 4) != 0) {
    uVar3 = (uint)param_2[1] *
            ((uint)((uint)*param_2 != ((int)(uint)*param_2 >> 3) * 8) + ((int)(uint)*param_2 >> 3))
            & 0xffff;
    if (*param_1 < 0x81) {
      if (*(int *)(param_2 + 2) == 0) {
        if ((*param_1 < 0x7f) && (0x1f < *param_1)) {
          return (*param_1 - 0x20 & 0xffff) * uVar3 + *(int *)(param_2 + 4);
        }
      }
      else {
        for (uVar2 = 0; uVar1 = FUN_0800549e(*(undefined4 *)(param_2 + 2)), uVar2 < uVar1;
            uVar2 = uVar2 + 1 & 0xffff) {
          if (*(byte *)(*(int *)(param_2 + 2) + uVar2) == *param_1) {
            return uVar2 * uVar3 + *(int *)(param_2 + 4);
          }
        }
      }
    }
    else {
      for (uVar2 = 0; uVar1 = FUN_0800549e(*(undefined4 *)(param_2 + 2)), uVar2 < uVar1 >> 1;
          uVar2 = uVar2 + 1 & 0xffff) {
        if ((*(byte *)(*(int *)(param_2 + 2) + uVar2 * 2) == *param_1) &&
           (*(byte *)(*(int *)(param_2 + 2) + uVar2 * 2 + 1) == param_1[1])) {
          return uVar2 * uVar3 + *(int *)(param_2 + 4);
        }
      }
    }
  }
  return 0;
}


/* 080103e0 FUN_080103e0 */

short FUN_080103e0(undefined4 param_1,short *param_2)

{
  short sVar1;
  
  sVar1 = FUN_0800549e(param_1);
  return *param_2 * sVar1;
}


/* 080103f4 FUN_080103f4 */

uint FUN_080103f4(uint param_1)

{
  int iVar1;
  
  FUN_0800aba6(DAT_08010414,param_1 & 0xff);
  do {
    iVar1 = FUN_0800aacc(DAT_08010414,0x80);
  } while (iVar1 == 0);
  return param_1;
}


/* 08010418 FUN_08010418 */

bool FUN_08010418(int param_1,uint param_2)

{
  if (5 < param_1) {
    if (*DAT_08010474 == 0) {
      FUN_0800f808(0,&DAT_080104dc,s____lib_easylogger_src_elog_c_080104bc,DAT_08010478,0x2a7,
                   s___s__has_assert_failed_at__s__ld_08010498,s_level_<__ELOG_LVL_VERBOSE_0801047c,
                   DAT_08010478,0x2a7);
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    (*(code *)*DAT_08010474)(s_level_<__ELOG_LVL_VERBOSE_0801047c,DAT_08010478,0x2a7);
  }
  return (*(uint *)(DAT_080104e4 + param_1 * 4) & param_2) != 0;
}


/* 080104e8 FUN_080104e8 */

undefined4 FUN_080104e8(void)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *DAT_0801052c;
  uVar1 = 0;
  if (*(int *)(iVar2 + 0x1c) <= *(int *)(*DAT_08010530 + 4)) {
    if ((*(int *)(*DAT_08010530 + 4) < *(int *)(iVar2 + 0x1c)) ||
       (*(int *)(iVar2 + 0x20) <= *(int *)(*DAT_08010530 + 4))) {
      if (*(int *)(iVar2 + 0x20) <= *(int *)(*DAT_08010530 + 4)) {
        uVar1 = 2;
      }
    }
    else {
      uVar1 = 1;
    }
  }
  return uVar1;
}


/* 08010534 FUN_08010534 */

void FUN_08010534(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,int param_7,undefined4 param_8,int param_9)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = 0;
  iVar3 = param_7 * -2 + 3;
  while (iVar1 <= param_7) {
    iVar2 = iVar1;
    if (param_9 == 0) {
      FUN_0801083a(param_1,param_2,param_3,param_4,param_5,param_6,iVar1,param_7,param_8);
    }
    else {
      for (; iVar2 <= param_7; iVar2 = iVar2 + 1) {
        FUN_0801083a(param_1,param_2,param_3,param_4,param_5,param_6,iVar1,iVar2,param_8);
      }
    }
    iVar1 = iVar1 + 1;
    if (iVar3 < 0) {
      iVar3 = iVar3 + iVar1 * 4 + 6;
    }
    else {
      iVar3 = iVar3 + (iVar1 - param_7) * 4 + 10;
      param_7 = param_7 + -1;
    }
  }
  return;
}


/* 080105a4 FUN_080105a4 */

void FUN_080105a4(int param_1,int param_2,int param_3,uint param_4,int param_5,int param_6,
                 undefined4 param_7,undefined4 param_8)

{
  if (param_4 != ((int)param_4 / 2) * 2) {
    param_4 = param_4 + 1 & 0xffff;
  }
  if (param_6 == 0) {
    FUN_08010952(param_1 + param_5 & 0xffff,param_2,param_3 + param_5 * -2 & 0xffff,param_7);
    FUN_08010952(param_1 + param_5 & 0xffff,(param_2 + param_4) - 1 & 0xffff,
                 param_3 + param_5 * -2 & 0xffff,param_8);
    FUN_08010972(param_1,param_2 + param_5 & 0xffff,(int)param_4 / 2 - param_5 & 0xffff,param_7);
    FUN_08010972(param_1,param_2 + (int)param_4 / 2 & 0xffff,(int)param_4 / 2 - param_5 & 0xffff,
                 param_8);
    FUN_08010972((param_1 + param_3) - 1U & 0xffff,param_2 + param_5 & 0xffff,
                 (int)param_4 / 2 - param_5 & 0xffff,param_7);
    FUN_08010972((param_1 + param_3) - 1U & 0xffff,param_2 + (int)param_4 / 2 & 0xffff,
                 (int)param_4 / 2 - param_5 & 0xffff,param_8);
  }
  else {
    FUN_08010992(param_1 + param_5 & 0xffff,param_2,param_3 + param_5 * -2 & 0xffff,
                 (param_4 - ((int)param_4 >> 0x1f)) * 0x8000 >> 0x10,param_7);
    FUN_08010992(param_1 + param_5 & 0xffff,param_2 + (int)param_4 / 2 & 0xffff,
                 param_3 + param_5 * -2 & 0xffff,(param_4 - ((int)param_4 >> 0x1f)) * 0x8000 >> 0x10
                 ,param_8);
    FUN_08010992(param_1,param_2 + param_5 & 0xffff,param_5,(int)param_4 / 2 - param_5 & 0xffff,
                 param_7);
    FUN_08010992(param_1,param_2 + (int)param_4 / 2 & 0xffff,param_5,
                 (int)param_4 / 2 - param_5 & 0xffff,param_8);
    FUN_08010992((param_1 + param_3) - param_5 & 0xffff,param_2 + param_5 & 0xffff,param_5,
                 (int)param_4 / 2 - param_5 & 0xffff,param_7);
    FUN_08010992((param_1 + param_3) - param_5 & 0xffff,param_2 + (int)param_4 / 2 & 0xffff,param_5,
                 (int)param_4 / 2 - param_5 & 0xffff,param_8);
  }
  FUN_08010534(param_1,param_2,param_1 + param_5 & 0xffff,param_2 + param_5 & 0xffff,
               param_1 + param_5 & 0xffff,param_2 + param_5 & 0xffff,param_5,param_7,param_6);
  FUN_08010534(param_1,(param_2 + param_4) - param_5 & 0xffff,param_1 + param_5 & 0xffff,
               (param_2 + param_4) - 1 & 0xffff,param_1 + param_5 & 0xffff,
               ((param_2 + param_4) - param_5) - 1 & 0xffff,param_5,param_8,param_6);
  FUN_08010534((param_1 + param_3) - param_5 & 0xffff,param_2,param_1 + param_3 & 0xffff,
               param_2 + param_5 & 0xffff,((param_1 + param_3) - param_5) - 1U & 0xffff,
               param_2 + param_5 & 0xffff,param_5,param_7,param_6);
  FUN_08010534((param_1 + param_3) - param_5 & 0xffff,(param_2 + param_4) - param_5 & 0xffff,
               param_1 + param_3 & 0xffff,(param_2 + param_4) - 1 & 0xffff,
               ((param_1 + param_3) - param_5) - 1U & 0xffff,
               ((param_2 + param_4) - param_5) - 1 & 0xffff,param_5,param_8,param_6);
  return;
}


/* 0801083a FUN_0801083a */

void FUN_0801083a(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 short param_5,short param_6,short param_7,short param_8,undefined4 param_9)

{
  FUN_08010922(param_1,param_2,param_3,param_4,param_5 + param_7,param_6 - param_8,param_9,param_1,
               param_2,param_3);
  FUN_08010922(param_1,param_2,param_3,param_4,param_5 + param_8,param_6 - param_7,param_9);
  FUN_08010922(param_1,param_2,param_3,param_4,param_5 + param_8,param_6 + param_7,param_9);
  FUN_08010922(param_1,param_2,param_3,param_4,param_5 + param_7,param_6 + param_8,param_9);
  FUN_08010922(param_1,param_2,param_3,param_4,param_5 - param_7,param_6 + param_8,param_9);
  FUN_08010922(param_1,param_2,param_3,param_4,param_5 - param_8,param_6 + param_7,param_9);
  FUN_08010922(param_1,param_2,param_3,param_4,param_5 - param_8,param_6 - param_7,param_9);
  FUN_08010922(param_1,param_2,param_3,param_4,param_5 - param_7,param_6 - param_8,param_9);
  return;
}


/* 08010922 FUN_08010922 */

void FUN_08010922(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 undefined4 param_7)

{
  if ((((param_5 <= param_3) && (param_1 <= param_5)) && (param_6 <= param_4)) &&
     (param_2 <= param_6)) {
    FUN_08009a24(param_5,param_6,param_7);
  }
  return;
}


/* 08010952 FUN_08010952 */

void FUN_08010952(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  if (param_3 != 0) {
    FUN_08011214(param_1,param_2,param_3,1,param_4);
  }
  return;
}


/* 08010972 FUN_08010972 */

void FUN_08010972(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  if (param_3 != 0) {
    FUN_08011214(param_1,param_2,1,param_3,param_4);
  }
  return;
}


/* 08010992 FUN_08010992 */

void FUN_08010992(undefined4 param_1,undefined4 param_2,int param_3,int param_4,undefined4 param_5)

{
  if ((param_3 != 0) && (param_4 != 0)) {
    FUN_08011214(param_1,param_2,param_3,param_4,param_5);
  }
  return;
}


/* 080109c0 FUN_080109c0 */

void FUN_080109c0(void)

{
  FUN_08005ffa(DAT_080109fc,0x80);
  FUN_08010a00(2);
  FUN_080098e2(DAT_080109fc,0x40);
  FUN_08010a00(2);
  FUN_08005ffa(DAT_080109fc,0x40);
  FUN_08010a00(2);
  FUN_080098e2(DAT_080109fc,0x80);
  FUN_08010a00(2);
  return;
}


/* 08010a00 FUN_08010a00 */

void FUN_08010a00(void)

{
  int iVar1;
  
  iVar1 = 10;
  do {
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


/* 08010a0e FUN_08010a0e */

undefined4 FUN_08010a0e(uint param_1,undefined4 param_2,uint param_3,undefined1 *param_4)

{
  undefined1 uVar1;
  
  FUN_08010c58();
  FUN_08010bb0((param_1 & 0x7f) << 1);
  FUN_08010bb0(param_2);
  FUN_08010c58();
  FUN_08010bb0(param_1 * 2 + 1 & 0xff);
  for (; param_3 != 0; param_3 = param_3 - 1 & 0xff) {
    if (param_3 == 1) {
      uVar1 = FUN_08010b5c(0);
      *param_4 = uVar1;
    }
    else {
      uVar1 = FUN_08010b5c(1);
      *param_4 = uVar1;
    }
    param_4 = param_4 + 1;
  }
  FUN_08010c8c();
  return 0;
}


/* 08010a6c FUN_08010a6c */

undefined4 FUN_08010a6c(uint param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  FUN_08010c58();
  FUN_08010bb0((param_1 & 0x7f) << 1);
  FUN_08010bb0(param_2);
  FUN_08010c8c();
  FUN_0800f418(1);
  FUN_08010c58();
  FUN_08010bb0(param_1 * 2 + 1 & 0xff);
  uVar1 = FUN_08010b5c(0);
  FUN_08010c8c();
  return uVar1;
}


/* 08010ab2 FUN_08010ab2 */

undefined4 FUN_08010ab2(uint param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_08010c58();
  FUN_08010bb0((param_1 & 0x7f) << 1);
  FUN_08010bb0(param_2);
  FUN_08010bb0(param_3);
  FUN_08010c8c();
  return 0;
}


/* 08010ae0 FUN_08010ae0 */

undefined8 FUN_08010ae0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined2 local_18;
  undefined1 local_16;
  undefined1 local_15;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 uStack_c;
  
  local_18 = (undefined2)param_1;
  local_16 = (undefined1)((uint)param_1 >> 0x10);
  local_15 = (undefined1)((uint)param_1 >> 0x18);
  local_14 = param_2;
  local_10 = param_3;
  uStack_c = param_4;
  FUN_0800a2b4(8,1);
  local_18 = 0x40;
  local_10 = 1;
  local_15 = 0;
  local_16 = 0x11;
  local_14 = CONCAT31(local_14._1_3_,1);
  FUN_080096d0(DAT_08010b24,&local_18);
  local_18 = 0x80;
  local_10 = 0x11;
  FUN_080096d0(DAT_08010b24,&local_18);
  return CONCAT44(local_14,CONCAT13(local_15,CONCAT12(local_16,local_18)));
}


/* 08010b28 FUN_08010b28 */

void FUN_08010b28(void)

{
  FUN_080098e2(DAT_08010b58,0x80);
  FUN_08010a00(2);
  FUN_080098e2(DAT_08010b58,0x40);
  FUN_08010a00(2);
  FUN_08005ffa(DAT_08010b58,0x40);
  FUN_08010a00(2);
  return;
}


/* 08010b5c FUN_08010b5c */

uint FUN_08010b5c(int param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 0;
  for (bVar1 = 0; bVar1 < 8; bVar1 = bVar1 + 1) {
    uVar3 = (uVar3 << 0x19) >> 0x18;
    FUN_080098e2(DAT_08010bac,0x40);
    FUN_08010a00(2);
    iVar2 = FUN_080098d0(DAT_08010bac,0x80);
    if (iVar2 != 0) {
      uVar3 = uVar3 + 1 & 0xff;
    }
    FUN_08005ffa(DAT_08010bac,0x40);
    FUN_08010a00(2);
  }
  if (param_1 == 0) {
    FUN_08010b28();
  }
  else {
    FUN_080109c0();
  }
  return uVar3;
}


/* 08010bb0 FUN_08010bb0 */

undefined4 FUN_08010bb0(uint param_1)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  
  bVar2 = 0;
  uVar4 = 0;
  for (bVar1 = 0; bVar1 < 8; bVar1 = bVar1 + 1) {
    if (param_1 >> 7 == 0) {
      FUN_08005ffa(DAT_08010c54,0x80);
    }
    else {
      FUN_080098e2(DAT_08010c54,0x80);
    }
    FUN_08010a00(2);
    FUN_080098e2(DAT_08010c54,0x40);
    FUN_08010a00(2);
    FUN_08005ffa(DAT_08010c54,0x40);
    param_1 = (param_1 << 0x19) >> 0x18;
  }
  FUN_080098e2(DAT_08010c54,0x80);
  FUN_08010a00(2);
  FUN_080098e2(DAT_08010c54,0x40);
  FUN_08010a00(2);
  do {
    iVar3 = FUN_080098d0(DAT_08010c54,0x80);
    if (iVar3 == 0) {
code_r0x08010c3e:
      FUN_08005ffa(DAT_08010c54,0x40);
      FUN_08010a00(2);
      return uVar4;
    }
    bVar2 = bVar2 + 1;
    if (0xfa < bVar2) {
      FUN_08010c8c();
      uVar4 = 1;
      goto code_r0x08010c3e;
    }
    FUN_08010a00(2);
  } while( true );
}


/* 08010c58 FUN_08010c58 */

void FUN_08010c58(void)

{
  FUN_080098e2(DAT_08010c88,0x80);
  FUN_080098e2(DAT_08010c88,0x40);
  FUN_08010a00(2);
  FUN_08005ffa(DAT_08010c88,0x80);
  FUN_08010a00(2);
  FUN_08005ffa(DAT_08010c88,0x40);
  return;
}


/* 08010c8c FUN_08010c8c */

void FUN_08010c8c(void)

{
  FUN_08005ffa(DAT_08010cb0,0x80);
  FUN_080098e2(DAT_08010cb0,0x40);
  FUN_08010a00(2);
  FUN_080098e2(DAT_08010cb0,0x80);
  return;
}


/* 08010cb4 FUN_08010cb4 */

int FUN_08010cb4(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  param_2 = param_2 + -1;
  iVar3 = -1;
  while (iVar2 <= param_2) {
    iVar1 = iVar2 + (param_2 - iVar2) / 2;
    if (param_3 < (int)(uint)*(ushort *)(param_1 + iVar1 * 2)) {
      param_2 = iVar1 + -1;
    }
    else {
      iVar2 = iVar1 + 1;
      iVar3 = iVar1;
    }
  }
  return iVar3;
}


/* 08010ce8 FUN_08010ce8 */

bool FUN_08010ce8(void)

{
  return *(char *)(DAT_08010cf8 + 4) == '\x02';
}


/* 08010cfc FUN_08010cfc */

undefined8 FUN_08010cfc(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined2 local_18;
  undefined2 uStack_16;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 uStack_c;
  
  local_18 = (undefined2)param_1;
  uStack_16 = (undefined2)((uint)param_1 >> 0x10);
  local_14 = param_2;
  local_10 = param_3;
  uStack_c = param_4;
  FUN_0800a2b4(0xc,1);
  FUN_080098b8(&local_18);
  local_18 = 0x10;
  local_10 = 0;
  local_14 = CONCAT31(local_14._1_3_,1);
  FUN_080096d0(DAT_08010d38,&local_18);
  local_18 = 0x8000;
  FUN_080096d0(DAT_08010d3c,&local_18);
  return CONCAT44(local_14,CONCAT22(uStack_16,local_18));
}


/* 08010d40 FUN_08010d40 */

void FUN_08010d40(undefined1 *param_1,int param_2)

{
  ushort uVar1;
  
  switch(*param_1) {
  case 0:
    if (param_2 == 1) {
      *param_1 = 1;
      *(undefined2 *)(param_1 + 4) = 0;
    }
    if ((param_1[2] == '\x03') && (param_1[6] != '\0')) {
      *(short *)(param_1 + 8) = *(short *)(param_1 + 8) + 1;
      if (*(ushort *)(param_1 + 8) < 0x22) {
        if (1 < (byte)param_1[6]) {
          param_1[1] = 3;
          param_1[6] = 0;
          *(undefined2 *)(param_1 + 8) = 0;
        }
      }
      else {
        param_1[1] = 1;
        param_1[6] = 0;
        *(undefined2 *)(param_1 + 8) = 0;
      }
    }
    break;
  case 1:
    if (param_2 == 1) {
      *(short *)(param_1 + 4) = *(short *)(param_1 + 4) + 1;
      if (5 < *(ushort *)(param_1 + 4)) {
        *param_1 = 2;
      }
    }
    else {
      *param_1 = 0;
    }
  case 2:
    if (param_1[2] == '\0') {
      *param_1 = 3;
      param_1[1] = 1;
    }
    else if (param_1[2] == '\x01') {
      *param_1 = 4;
      param_1[1] = 1;
      *(undefined2 *)(param_1 + 10) = 0;
    }
    else if ((param_1[2] == '\x02') || (param_1[2] == '\x03')) {
      if (param_2 == 1) {
        *(short *)(param_1 + 4) = *(short *)(param_1 + 4) + 1;
        if (*(short *)(param_1 + 0xc) == 0) {
          uVar1 = 0x37;
        }
        else {
          uVar1 = *(ushort *)(param_1 + 0xc) / 10;
        }
        if (uVar1 <= *(ushort *)(param_1 + 4)) {
          param_1[1] = 2;
          *param_1 = 3;
        }
      }
      else if (param_1[2] == '\x02') {
        param_1[1] = 1;
        *param_1 = 0;
      }
      else if (param_1[2] == '\x03') {
        param_1[6] = param_1[6] + '\x01';
        *(undefined2 *)(param_1 + 8) = 0;
        *param_1 = 0;
      }
    }
    break;
  case 3:
    if (param_2 == 0) {
      *param_1 = 0;
    }
    break;
  case 4:
    *(short *)(param_1 + 10) = *(short *)(param_1 + 10) + 1;
    if ((0x14 < *(ushort *)(param_1 + 10)) || (param_2 == 0)) {
      *param_1 = 0;
    }
  }
  return;
}


/* 08010e50 FUN_08010e50 */

void FUN_08010e50(void)

{
  bool bVar1;
  bool bVar2;
  byte *pbVar3;
  int iVar4;
  
  iVar4 = FUN_080098d0(DAT_08010ee0,0x8000);
  bVar1 = iVar4 == 0;
  iVar4 = FUN_080098d0(DAT_08010ee4,0x10);
  bVar2 = iVar4 == 0;
  if (*DAT_08010ee8 == '\0') {
    FUN_08010d40(DAT_08010eec,bVar1);
    FUN_08010d40(DAT_08010ef0,bVar2);
  }
  else if ((!bVar1) && (!bVar2)) {
    *DAT_08010ee8 = '\0';
    pbVar3 = DAT_08010eec;
    *DAT_08010eec = 0;
    pbVar3[6] = 0;
    pbVar3 = DAT_08010ef0;
    *DAT_08010ef0 = 0;
    pbVar3[6] = 0;
  }
  if (((*DAT_08010ee8 == '\0') && (1 < *DAT_08010eec)) && (1 < *DAT_08010ef0)) {
    DAT_08010eec[1] = 1;
    DAT_08010ef0[1] = 1;
    *DAT_08010ee8 = '\x01';
  }
  if (((bVar1) && (1 < *DAT_08010eec)) || ((bVar2 && (1 < *DAT_08010ef0)))) {
    FUN_0800f230();
  }
  return;
}


/* 08010ef4 FUN_08010ef4 */

void FUN_08010ef4(undefined1 param_1)

{
  undefined1 *puVar1;
  
  DAT_08010f04[2] = param_1;
  puVar1 = DAT_08010f04;
  DAT_08010f04[1] = 0;
  *puVar1 = 3;
  return;
}


/* 08010f08 FUN_08010f08 */

void FUN_08010f08(undefined1 param_1)

{
  DAT_08010f1c[2] = param_1;
  *(undefined1 *)(DAT_08010f20 + 1) = 0;
  *DAT_08010f1c = 3;
  return;
}


/* 08010f24 FUN_08010f24 */

undefined1 FUN_08010f24(void)

{
  undefined1 uVar1;
  
  uVar1 = *(undefined1 *)(DAT_08010f30 + 1);
  *(undefined1 *)(DAT_08010f30 + 1) = 0;
  return uVar1;
}


/* 08010f34 FUN_08010f34 */

undefined1 FUN_08010f34(void)

{
  undefined1 uVar1;
  
  uVar1 = *(undefined1 *)(DAT_08010f40 + 1);
  *(undefined1 *)(DAT_08010f40 + 1) = 0;
  return uVar1;
}


/* 08010f44 FUN_08010f44 */

void FUN_08010f44(int param_1)

{
  if (param_1 == 0) {
    FUN_080098e2(DAT_08010f60,0x40);
  }
  else {
    FUN_08005ffa(DAT_08010f60,0x40);
  }
  return;
}


/* 08010f64 FUN_08010f64 */

void FUN_08010f64(uint param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 undefined4 param_7)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  
  if (((int)param_1 < param_3) && (param_2 < param_4)) {
    if (0x9f < param_3) {
      param_3 = 0x9f;
    }
    if (0x27 < param_4) {
      param_4 = 0x27;
    }
    uVar3 = ((param_4 - param_2) + 1) - param_6 & 0xffff;
    for (; (int)param_1 <= param_3; param_1 = param_1 + 1) {
      if (param_5 == 0) {
        for (iVar2 = 0; iVar2 < (int)uVar3; iVar2 = iVar2 + 1) {
          uVar1 = FUN_08011330(param_1 & 0xffff,param_2 + param_6 + iVar2 & 0xffff);
          FUN_08009a24(param_1 & 0xffff,param_2 + iVar2 & 0xffff,uVar1);
        }
        for (iVar2 = 0; iVar2 < param_6; iVar2 = iVar2 + 1) {
          FUN_08009a24(param_1 & 0xffff,param_4 - iVar2 & 0xffff,param_7);
        }
      }
      else {
        for (iVar2 = 0; iVar2 < (int)uVar3; iVar2 = iVar2 + 1) {
          uVar1 = FUN_08011330(param_1 & 0xffff,(param_4 - param_6) - iVar2 & 0xffff);
          FUN_08009a24(param_1 & 0xffff,param_4 - iVar2 & 0xffff,uVar1);
        }
        for (iVar2 = 0; iVar2 < param_6; iVar2 = iVar2 + 1) {
          FUN_08009a24(param_1 & 0xffff,param_2 + iVar2 & 0xffff,param_7);
        }
      }
    }
  }
  return;
}


/* 0801103a FUN_0801103a */

void FUN_0801103a(uint param_1,uint param_2,short param_3,short param_4,undefined2 *param_5)

{
  uint uVar1;
  int iVar2;
  int local_28;
  
  iVar2 = (int)(short)((short)param_1 + param_3 + -1);
  local_28 = (int)(short)((short)param_2 + param_4 + -1);
  if (0x9f < iVar2) {
    iVar2 = 0x9f;
  }
  if (0x27 < local_28) {
    local_28 = 0x27;
  }
  for (; uVar1 = param_1, (int)param_2 <= local_28; param_2 = (uint)(short)((short)param_2 + 1)) {
    for (; (int)uVar1 <= iVar2; uVar1 = (int)(short)((short)uVar1 + 1)) {
      if ((-1 < (int)uVar1) && (-1 < (int)param_2)) {
        FUN_08009a24(uVar1 & 0xffff,param_2 & 0xffff,*param_5);
      }
      param_5 = param_5 + 1;
    }
  }
  return;
}


/* 080110a8 FUN_080110a8 */

void FUN_080110a8(undefined4 param_1,undefined4 param_2)

{
  undefined1 local_3c;
  undefined1 local_3b;
  undefined1 local_3a;
  undefined1 local_39;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  FUN_0800a254(1);
  FUN_0800939c(DAT_08011130);
  local_38 = DAT_08011134;
  local_30 = 0x10;
  local_28 = 0;
  local_24 = 0x80;
  local_20 = 0x100;
  local_1c = 0x400;
  local_18 = 0;
  local_14 = 0x3000;
  local_10 = 0;
  local_34 = param_1;
  local_2c = param_2;
  FUN_080094cc(DAT_08011130,&local_38);
  FUN_08009508(0xd,DAT_08011130 + -0x1c,DAT_08011130,1);
  FUN_08009388(DAT_08011130,2,1);
  local_3c = 0xc;
  local_39 = 1;
  local_3b = 0;
  local_3a = 0;
  FUN_0800a180(&local_3c);
  FUN_08009484(DAT_08011130,1);
  return;
}


/* 08011138 FUN_08011138 */

void FUN_08011138(uint param_1,uint param_2,int param_3,int param_4,int param_5,undefined4 param_6,
                 undefined4 param_7)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int local_2c;
  uint local_28;
  
  if (((int)param_1 <= (int)(uint)*(ushort *)(DAT_08011210 + 8)) &&
     ((int)param_2 <= (int)(uint)*(ushort *)(DAT_08011210 + 10))) {
    iVar2 = (uint)(param_4 != ((int)(param_4 + ((uint)(param_4 >> 0x1f) >> 0x1d)) >> 3) * 8) +
            (param_4 >> 3);
    uVar1 = param_1;
    for (iVar3 = 0; iVar3 < param_5; iVar3 = iVar3 + 1) {
      for (iVar4 = 0; iVar4 < iVar2; iVar4 = iVar4 + 1) {
        local_28 = (uint)*(byte *)(param_3 + iVar3 * iVar2 + iVar4);
        for (local_2c = 0; local_2c < 8; local_2c = local_2c + 1) {
          if ((-1 < (int)uVar1) && (-1 < (int)param_2)) {
            if ((local_28 & 0x80) == 0) {
              FUN_08009a24(uVar1 & 0xffff,param_2 & 0xffff,param_7);
            }
            else {
              FUN_08009a24(uVar1 & 0xffff,param_2 & 0xffff,param_6);
            }
          }
          local_28 = (local_28 << 0x19) >> 0x18;
          uVar1 = (uint)(short)((short)uVar1 + 1);
          if ((uVar1 - param_1 == param_4) ||
             ((int)(uint)*(ushort *)(DAT_08011210 + 8) < (int)uVar1)) {
            param_2 = (uint)(short)((short)param_2 + 1);
            uVar1 = param_1;
            if ((int)(uint)*(ushort *)(DAT_08011210 + 10) < (int)param_2) {
              return;
            }
            break;
          }
        }
        if (uVar1 == param_1) break;
      }
    }
  }
  return;
}


/* 08011214 FUN_08011214 */

void FUN_08011214(uint param_1,uint param_2,int param_3,int param_4,undefined4 param_5)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = (param_1 + param_3) - 1 & 0xffff;
  uVar3 = (param_2 + param_4) - 1 & 0xffff;
  if ((int)param_1 < (int)(uint)*(ushort *)(DAT_08011290 + 4)) {
    param_1 = (uint)*(ushort *)(DAT_08011290 + 4);
  }
  if (*(ushort *)(DAT_08011290 + 8) < uVar2) {
    uVar2 = (uint)*(ushort *)(DAT_08011290 + 8);
  }
  if ((int)param_2 < (int)(uint)*(ushort *)(DAT_08011290 + 6)) {
    param_2 = (uint)*(ushort *)(DAT_08011290 + 6);
  }
  if (*(ushort *)(DAT_08011290 + 10) < uVar3) {
    uVar3 = (uint)*(ushort *)(DAT_08011290 + 10);
  }
  for (; uVar1 = param_1, (int)param_2 <= (int)uVar3; param_2 = param_2 + 1 & 0xffff) {
    for (; (int)uVar1 <= (int)uVar2; uVar1 = uVar1 + 1 & 0xffff) {
      FUN_08009a24(uVar1,param_2,param_5);
    }
  }
  return;
}


/* 08011294 FUN_08011294 */

void FUN_08011294(uint param_1,uint param_2,int param_3,int param_4,undefined4 param_5,
                 undefined4 param_6,int param_7)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = (param_1 + param_3) - 1 & 0xffff;
  uVar4 = (param_2 + param_4) - 1 & 0xffff;
  if ((int)param_1 < (int)(uint)*(ushort *)(DAT_0801132c + 4)) {
    param_1 = (uint)*(ushort *)(DAT_0801132c + 4);
  }
  if (*(ushort *)(DAT_0801132c + 8) < uVar3) {
    uVar3 = (uint)*(ushort *)(DAT_0801132c + 8);
  }
  if ((int)param_2 < (int)(uint)*(ushort *)(DAT_0801132c + 6)) {
    param_2 = (uint)*(ushort *)(DAT_0801132c + 6);
  }
  if (*(ushort *)(DAT_0801132c + 10) < uVar4) {
    uVar4 = (uint)*(ushort *)(DAT_0801132c + 10);
  }
  for (; uVar2 = param_1, (int)param_2 <= (int)uVar4; param_2 = param_2 + 1 & 0xffff) {
    for (; (int)uVar2 <= (int)uVar3; uVar2 = uVar2 + 1 & 0xffff) {
      iVar1 = FUN_08011330(uVar2,param_2);
      if (iVar1 == param_7) {
        FUN_08009a24(uVar2,param_2,param_6);
      }
      else {
        FUN_08009a24(uVar2,param_2,param_5);
      }
    }
  }
  return;
}


/* 08011330 FUN_08011330 */

undefined2 FUN_08011330(uint param_1,uint param_2,undefined4 param_3,uint param_4)

{
  uint unaff_r4;
  
  if (*(char *)(DAT_08011368 + 1) == '\0') {
    param_4 = 0x27 - param_2 & 0xffff;
    unaff_r4 = param_1;
  }
  else if (*(char *)(DAT_08011368 + 1) == '\x01') {
    param_4 = param_2;
    unaff_r4 = 0x9f - param_1 & 0xffff;
  }
  return *(undefined2 *)(DAT_0801136c + (param_4 + unaff_r4 * 0x28) * 2);
}


/* 08011370 FUN_08011370 */

void FUN_08011370(void)

{
  do {
  } while (*DAT_080113ec == '\0');
  FUN_080099e8(0,0,0x27,0x9f);
  FUN_0800a486(DAT_080113f0,0);
  FUN_0800a474(DAT_080113f0,0x800);
  FUN_0800a486(DAT_080113f0,1);
  FUN_080110a8(DAT_080113f4,0x1900);
  FUN_08005ffa(DAT_080113f8,0x400);
  FUN_08009484(DAT_080113fc,0);
  FUN_08005fec(0xf0,DAT_080113fc + -0x1c);
  FUN_08005ff4(DAT_080113fc,0x1900);
  FUN_08009484(DAT_080113fc,1);
  FUN_0800a49e(DAT_080113f0,2,1);
  *DAT_080113ec = '\0';
  return;
}


/* 08011400 FUN_08011400 */

void FUN_08011400(void)

{
  *DAT_08011418 = '\0';
  FUN_08011370();
  do {
  } while (*DAT_08011418 == '\0');
  return;
}


/* 0801141c FUN_0801141c */

void FUN_0801141c(int param_1,int param_2)

{
  uint uVar1;
  
  *DAT_080114c0 = '\0';
  do {
  } while (*DAT_080114c4 == '\0');
  FUN_080099e8(0,param_1,0x27,param_2);
  FUN_0800a486(DAT_080114c8,0);
  FUN_0800a474(DAT_080114c8,0x800);
  FUN_0800a486(DAT_080114c8,1);
  uVar1 = ((param_2 - param_1) + 1) * 0x28;
  FUN_080110a8(DAT_080114cc + param_1 * 0x50,uVar1);
  FUN_08005ffa(DAT_080114d0,0x400);
  FUN_08009484(DAT_080114d4,0);
  FUN_08005fec(0xf0,DAT_080114d4 + -0x1c);
  FUN_08005ff4(DAT_080114d4,uVar1 & 0xffff);
  FUN_08009484(DAT_080114d4,1);
  FUN_0800a49e(DAT_080114c8,2,1);
  *DAT_080114c4 = '\0';
  do {
  } while (*DAT_080114c0 == '\0');
  return;
}


/* 080114d8 FUN_080114d8 */

void FUN_080114d8(short param_1,short param_2,short param_3,short param_4)

{
  int iVar1;
  
  iVar1 = DAT_080114f0;
  *(short *)(DAT_080114f0 + 4) = param_1;
  *(short *)(iVar1 + 6) = param_2;
  iVar1 = DAT_080114f0;
  *(short *)(DAT_080114f0 + 8) = param_1 + param_3 + -1;
  *(short *)(iVar1 + 10) = param_2 + param_4 + -1;
  return;
}


/* 080114f4 FUN_080114f4 */

void FUN_080114f4(undefined1 param_1)

{
  *(undefined1 *)(DAT_080114fc + 1) = param_1;
  return;
}


/* 08011500 FUN_08011500 */

void FUN_08011500(int param_1,int param_2,byte *param_3,short *param_4,undefined4 param_5,
                 undefined4 param_6)

{
  short sVar1;
  int iVar2;
  
  if ((param_1 <= (int)(uint)*(ushort *)(DAT_0801159c + 8)) &&
     (param_2 <= (int)(uint)*(ushort *)(DAT_0801159c + 10))) {
    do {
      if (*param_3 == 0) {
        return;
      }
      sVar1 = (short)param_1;
      if (*param_3 < 0x81) {
        if (*param_3 == 0x20) {
          param_1 = (int)(short)(*param_4 + sVar1);
        }
        else {
          iVar2 = FUN_08010324(param_3,param_4);
          if (iVar2 != 0) {
            FUN_08011138(param_1,param_2,iVar2,*param_4,param_4[1],param_5,param_6);
            param_1 = (int)(short)(*param_4 + sVar1);
          }
        }
        param_3 = param_3 + 1;
      }
      else {
        iVar2 = FUN_08010324(param_3,param_4 + 6);
        if (iVar2 != 0) {
          FUN_08011138(param_1,param_2,iVar2,param_4[6],param_4[7],param_5,param_6);
          param_1 = (int)(short)(param_4[6] + sVar1);
        }
        param_3 = param_3 + 2;
      }
    } while (param_1 < 0xa0);
  }
  return;
}


/* 080115a0 FUN_080115a0 */

void FUN_080115a0(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,
                 ushort *param_5,undefined4 param_6,undefined4 param_7)

{
  ushort uVar1;
  uint uVar2;
  
  uVar1 = FUN_0800549e(param_4);
  uVar2 = (uint)uVar1 * (uint)*param_5 & 0xffff;
  if (param_3 < (int)uVar2) {
    FUN_08011500(param_1,param_2,param_4,param_5,param_6,param_7);
  }
  else {
    FUN_08011500((int)(short)((short)param_1 + (short)((int)(param_3 - uVar2) >> 1)),param_2,param_4
                 ,param_5,param_6,param_7);
  }
  return;
}


/* 080115f4 FUN_080115f4 */

void FUN_080115f4(undefined4 param_1,undefined4 param_2,char *param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  char *pcStack_c;
  undefined4 uStack_8;
  
  pcStack_c = param_3;
  uStack_8 = param_4;
  FUN_0800a1f0(0x500);
  FUN_0800a204(DAT_08011754,0);
  FUN_0800afbc();
  FUN_080135c8(0xe1000);
  FUN_0800adf0();
  FUN_0800e490();
  FUN_08010cfc();
  FUN_080123a8();
  FUN_0800df64();
  FUN_08010ae0();
  FUN_08012adc();
  FUN_08009b5c();
  FUN_08011214(0,0,0xa0,0x28,0);
  FUN_08011400();
  FUN_0800f418(0x14);
  FUN_08010f44(1);
  FUN_08012ba4();
  FUN_080133d0();
  FUN_0800e3a0();
  FUN_0800e1f4(0x50);
  FUN_0800f418(0x14);
  FUN_0800e1f4(0);
  FUN_080134a4();
  FUN_0801352c();
  FUN_080135ac(DAT_08011758);
  uVar2 = FUN_0800ef04();
  puVar1 = DAT_0801175c;
  *DAT_0801175c = uVar2;
  uStack_8 = *puVar1;
  pcStack_c = s_ch224__d_08011760;
  FUN_0800f808(4,&DAT_08011788,s____src_main_src_main_c_08011770,DAT_0801176c,0x85);
  FUN_08009910(500);
  FUN_08012e38();
  FUN_0800f2b0();
  FUN_08014cfc();
  *DAT_08011790 = 1;
  FUN_0800e17c();
  do {
    iVar3 = FUN_08011fa8();
    if (0x13 < (uint)(iVar3 - *DAT_08011794)) {
      iVar3 = FUN_08011fa8();
      *DAT_08011794 = iVar3;
      FUN_0801220c();
      FUN_0800ed78();
    }
    iVar3 = FUN_08011fa8();
    if (999 < (uint)(iVar3 - DAT_08011794[1])) {
      iVar3 = FUN_08011fa8();
      DAT_08011794[1] = iVar3;
      FUN_08011fb4();
    }
    iVar3 = FUN_08011fa8();
    if (4 < (uint)(iVar3 - DAT_08011794[2])) {
      iVar3 = FUN_08011fa8();
      DAT_08011794[2] = iVar3;
      if ((*(byte *)(DAT_08011798 + 0x1c) & 8) == 0) {
        FUN_08012c54(&pcStack_c);
        FUN_0800dd54(&pcStack_c);
        FUN_0800d2bc(&pcStack_c);
      }
    }
    iVar3 = FUN_08011fa8();
    if (0x31 < (uint)(iVar3 - DAT_08011794[3])) {
      iVar3 = FUN_08011fa8();
      DAT_08011794[3] = iVar3;
      FUN_08014ce0(0x32);
      FUN_08011370();
      FUN_08009908();
    }
  } while( true );
}


/* 0801179c FUN_0801179c */

bool FUN_0801179c(void)

{
  return *DAT_080117ac == 0;
}


/* 080117b0 FUN_080117b0 */

void FUN_080117b0(int param_1,int param_2,int param_3)

{
  FUN_08005352(param_1,param_2,2,DAT_080117d4);
  FUN_0800e15e(param_1 + (param_2 - param_3 & 0xfffffffeU),param_3);
  return;
}


/* 080117d8 FUN_080117d8 */

void FUN_080117d8(void)

{
  int iVar1;
  
  iVar1 = DAT_08011848;
  *(undefined1 *)(DAT_08011848 + 9) = 0;
  *(undefined1 *)(iVar1 + 10) = *(undefined1 *)(*DAT_0801184c + 0x50);
  iVar1 = DAT_08011850;
  *(undefined1 *)(DAT_08011850 + 9) = 0;
  *(undefined1 *)(iVar1 + 10) = *(undefined1 *)(*DAT_0801184c + 0x2c);
  if ((*(char *)(DAT_08011854 + 0x20) == '\0') && (2 < *(byte *)(*DAT_0801184c + 0x2c))) {
    *(char *)(iVar1 + 10) = *(char *)(*DAT_0801184c + 0x2c) + -2;
  }
  iVar1 = DAT_08011858;
  *(undefined1 *)(DAT_08011858 + 9) = 0;
  *(undefined1 *)(iVar1 + 10) = *(undefined1 *)(*DAT_0801184c + 0x51);
  iVar1 = DAT_0801185c;
  *(undefined1 *)(DAT_0801185c + 9) = 0;
  *(undefined1 *)(iVar1 + 10) = *(undefined1 *)(*DAT_08011860 + 4);
  iVar1 = DAT_08011864;
  *(undefined1 *)(DAT_08011864 + 9) = 0;
  *(undefined1 *)(iVar1 + 10) = *(undefined1 *)(*DAT_0801184c + 0x52);
  return;
}


/* 08011868 FUN_08011868 */

void FUN_08011868(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char cVar6;
  
  *DAT_08011b6c = DAT_08011b68;
  iVar3 = DAT_08011b68;
  *(undefined1 *)(DAT_08011b68 + 9) = 0;
  *(undefined1 *)(iVar3 + 8) = 0x10;
  *(int *)(iVar3 + 4) = DAT_08011b70;
  *(undefined1 *)(iVar3 + 10) = 0;
  for (iVar3 = 0; iVar4 = DAT_08011b70, iVar3 < 0x10; iVar3 = iVar3 + 1) {
    *(undefined4 *)(DAT_08011b70 + iVar3 * 0x18) =
         *(undefined4 *)(DAT_08011b78 + (uint)*(byte *)(*DAT_08011b74 + 4) * 0x40 + iVar3 * 4);
    *(undefined4 *)(iVar4 + iVar3 * 0x18 + 0xc) = DAT_08011b7c;
    *(undefined4 *)(iVar4 + iVar3 * 0x18 + 0x10) = 0;
    *(undefined4 *)(iVar4 + iVar3 * 0x18 + 0x14) = 0;
  }
  *(undefined4 *)(DAT_08011b70 + 0xc) = DAT_08011b80;
  iVar3 = DAT_08011b70;
  *(undefined4 *)(DAT_08011b70 + 0x24) = DAT_08011b84;
  *(undefined4 *)(iVar3 + 0x3c) = DAT_08011b88;
  *(undefined4 *)(iVar3 + 0x54) = DAT_08011b8c;
  *(undefined4 *)(iVar3 + 0x6c) = DAT_08011b90;
  *(undefined4 *)(iVar3 + 0x84) = DAT_08011b94;
  *(undefined4 *)(iVar3 + 0x9c) = DAT_08011b98;
  *(int *)(iVar3 + 0xbc) = DAT_08011b9c;
  *(undefined4 *)(iVar3 + 0xcc) = DAT_08011ba0;
  *(int *)(iVar3 + 0xec) = DAT_08011ba4;
  *(int *)(iVar3 + 0x104) = DAT_08011ba8;
  *(int *)(iVar3 + 0x11c) = DAT_08011bac;
  *(int *)(iVar3 + 0x134) = DAT_08011bb0;
  *(undefined4 *)(iVar3 + 0x144) = DAT_08011bb4;
  *(undefined4 *)(iVar3 + 0x15c) = DAT_08011bb8;
  *(undefined4 *)(iVar3 + 0x174) = DAT_08011bbc;
  *(undefined4 *)(DAT_08011b70 + 4) = DAT_08011bc0;
  iVar3 = DAT_08011b70;
  *(undefined4 *)(DAT_08011b70 + 0x1c) = DAT_08011bc4;
  *(undefined4 *)(iVar3 + 0x34) = DAT_08011bc8;
  *(undefined4 *)(iVar3 + 0x4c) = DAT_08011bcc;
  *(undefined4 *)(iVar3 + 100) = DAT_08011bd0;
  *(undefined4 *)(iVar3 + 0x7c) = DAT_08011bd4;
  *(undefined4 *)(iVar3 + 0x94) = DAT_08011bd8;
  *(undefined4 *)(iVar3 + 0xac) = DAT_08011bdc;
  *(undefined4 *)(iVar3 + 0xc4) = DAT_08011be0;
  *(undefined4 *)(iVar3 + 0xdc) = DAT_08011be4;
  *(undefined4 *)(iVar3 + 0xf4) = DAT_08011be8;
  *(undefined4 *)(iVar3 + 0x10c) = DAT_08011bec;
  *(undefined4 *)(iVar3 + 0x124) = DAT_08011bf0;
  *(undefined4 *)(iVar3 + 0x13c) = DAT_08011bf4;
  *(undefined4 *)(iVar3 + 0x154) = DAT_08011bf8;
  *(undefined4 *)(iVar3 + 0x16c) = DAT_08011bfc;
  iVar3 = DAT_08011bb0;
  *(undefined1 *)(DAT_08011bb0 + 9) = 0;
  *(undefined1 *)(iVar3 + 8) = 2;
  *(int *)(iVar3 + 4) = DAT_08011c00;
  *(undefined1 *)(iVar3 + 10) = *(undefined1 *)(*DAT_08011c04 + 0x50);
  for (iVar3 = 0; iVar5 = DAT_08011c00, iVar4 = DAT_08011b9c, iVar3 < 2; iVar3 = iVar3 + 1) {
    *(undefined4 *)(DAT_08011c00 + iVar3 * 0x18) =
         *(undefined4 *)(DAT_08011c08 + (uint)*(byte *)(*DAT_08011b74 + 4) * 8 + iVar3 * 4);
    *(int *)(iVar5 + iVar3 * 0x18 + 0x10) = DAT_08011b68;
    *(undefined4 *)(iVar5 + iVar3 * 0x18 + 0x14) = 0;
    *(undefined4 *)(iVar5 + iVar3 * 0x18 + 0xc) = DAT_08011c0c;
  }
  iVar5 = 8;
  cVar6 = *(char *)(*DAT_08011c04 + 0x2c);
  iVar3 = DAT_08011c10;
  if (*(char *)(DAT_08011c14 + 0x20) == '\0') {
    iVar5 = 6;
    iVar3 = DAT_08011c18;
    if (2 < *(byte *)(*DAT_08011c04 + 0x2c)) {
      cVar6 = *(char *)(*DAT_08011c04 + 0x2c) + -2;
    }
  }
  *(undefined1 *)(DAT_08011b9c + 9) = 0;
  *(char *)(iVar4 + 8) = (char)iVar5;
  *(int *)(iVar4 + 4) = DAT_08011c1c;
  *(char *)(iVar4 + 10) = cVar6;
  for (iVar4 = 0; iVar2 = DAT_08011c1c, iVar1 = DAT_08011ba4, iVar4 < iVar5; iVar4 = iVar4 + 1) {
    *(undefined4 *)(DAT_08011c1c + iVar4 * 0x18) = *(undefined4 *)(iVar3 + iVar4 * 4);
    *(int *)(iVar2 + iVar4 * 0x18 + 0x10) = DAT_08011b68;
    *(undefined4 *)(iVar2 + iVar4 * 0x18 + 0x14) = 0;
    *(undefined4 *)(iVar2 + iVar4 * 0x18 + 0xc) = DAT_08011c20;
  }
  *(undefined1 *)(DAT_08011ba4 + 9) = 0;
  *(undefined1 *)(iVar1 + 8) = 2;
  *(int *)(iVar1 + 4) = DAT_08011c24;
  *(undefined1 *)(iVar1 + 10) = *(undefined1 *)(*DAT_08011c04 + 0x51);
  for (iVar3 = 0; iVar5 = DAT_08011c24, iVar4 = DAT_08011ba8, iVar3 < 2; iVar3 = iVar3 + 1) {
    *(undefined4 *)(DAT_08011c24 + iVar3 * 0x18) = *(undefined4 *)(DAT_08011c28 + iVar3 * 4);
    *(int *)(iVar5 + iVar3 * 0x18 + 0x10) = DAT_08011b68;
    *(undefined4 *)(iVar5 + iVar3 * 0x18 + 0x14) = 0;
    *(undefined4 *)(iVar5 + iVar3 * 0x18 + 0xc) = DAT_08011c2c;
  }
  *(undefined1 *)(DAT_08011ba8 + 9) = 0;
  *(undefined1 *)(iVar4 + 8) = 4;
  *(int *)(iVar4 + 4) = DAT_08011c30;
  *(undefined1 *)(iVar4 + 10) = *(undefined1 *)(*DAT_08011b74 + 4);
  for (iVar3 = 0; iVar5 = DAT_08011c30, iVar4 = DAT_08011bac, iVar3 < 4; iVar3 = iVar3 + 1) {
    *(undefined4 *)(DAT_08011c30 + iVar3 * 0x18) = *(undefined4 *)(DAT_08011c34 + iVar3 * 4);
    *(int *)(iVar5 + iVar3 * 0x18 + 0x10) = DAT_08011b68;
    *(undefined4 *)(iVar5 + iVar3 * 0x18 + 0x14) = 0;
    *(undefined4 *)(iVar5 + iVar3 * 0x18 + 0xc) = DAT_08011c38;
  }
  *(undefined1 *)(DAT_08011bac + 9) = 0;
  *(undefined1 *)(iVar4 + 8) = 3;
  *(int *)(iVar4 + 4) = DAT_08011c3c;
  *(undefined1 *)(iVar4 + 10) = *(undefined1 *)(*DAT_08011c04 + 0x52);
  for (iVar3 = 0; iVar4 = DAT_08011c3c, iVar3 < 3; iVar3 = iVar3 + 1) {
    *(undefined4 *)(DAT_08011c3c + iVar3 * 0x18) =
         *(undefined4 *)(DAT_08011c40 + (uint)*(byte *)(*DAT_08011b74 + 4) * 0xc + iVar3 * 4);
    *(int *)(iVar4 + iVar3 * 0x18 + 0x10) = DAT_08011b68;
    *(undefined4 *)(iVar4 + iVar3 * 0x18 + 0x14) = 0;
    *(undefined4 *)(iVar4 + iVar3 * 0x18 + 0xc) = DAT_08011c44;
  }
  return;
}


/* 08011c48 FUN_08011c48 */

void FUN_08011c48(void)

{
  *DAT_08011c50 = 0;
  return;
}


/* 08011c54 FUN_08011c54 */

void FUN_08011c54(void)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (*DAT_08011eb4 == '\0') {
    *DAT_08011eb4 = '\x01';
    *DAT_08011eb8 = 100;
    FUN_0800ca90(*DAT_08011ebc,2);
    cVar2 = FUN_0800cbcc(*DAT_08011ebc);
    pcVar1 = DAT_08011ec0;
    *DAT_08011ec0 = cVar2;
    FUN_0800cac4(*DAT_08011ebc,*pcVar1);
    FUN_0800f1cc(0);
    FUN_08010ef4(2);
    FUN_08010f08(2);
  }
  iVar3 = FUN_08010f24();
  iVar4 = FUN_08010f34();
  iVar5 = iVar4;
  if (*(char *)(*DAT_08011ec4 + 0x52) != '\0') {
    iVar5 = iVar3;
    iVar3 = iVar4;
  }
  if (iVar5 == 2) {
    *DAT_08011eb4 = '\0';
    FUN_0800cc64(*DAT_08011ebc,*DAT_08011ec0);
    if (*(int *)(*DAT_08011ec8 + 0xc) != 0) {
      (**(code **)(*DAT_08011ec8 + 0xc))(0,*DAT_08011ec0);
      return;
    }
  }
  else if (iVar5 == 1) {
    *DAT_08011eb8 = 100;
    pcVar1 = DAT_08011ec0;
    *DAT_08011ec0 = *DAT_08011ec0 + '\x01';
    if ((int)(uint)*(byte *)(*DAT_08011ebc + 8) <= (int)*pcVar1) {
      *DAT_08011ec0 = '\0';
    }
    *DAT_08011ec8 = *(int *)(*DAT_08011ebc + 4) + *DAT_08011ec0 * 0x18;
    *(char *)(*DAT_08011ebc + 9) = *(char *)(*DAT_08011ebc + 9) + '\x01';
    if ('\x01' < *(char *)(*DAT_08011ebc + 9)) {
      *(undefined1 *)(*DAT_08011ebc + 9) = 1;
    }
    if ((*(byte *)(*DAT_08011ebc + 8) < 3) &&
       ((int)(uint)*(byte *)(*DAT_08011ebc + 8) <= (int)*(char *)(*DAT_08011ebc + 9))) {
      *(char *)(*DAT_08011ebc + 9) = *(char *)(*DAT_08011ebc + 8) + -1;
    }
    if (*DAT_08011ec0 == '\0') {
      *(undefined1 *)(*DAT_08011ebc + 9) = 0;
    }
    FUN_0800cac4(*DAT_08011ebc,*DAT_08011ec0);
  }
  else if (iVar3 == 1) {
    *DAT_08011eb8 = 100;
    pcVar1 = DAT_08011ec0;
    *DAT_08011ec0 = *DAT_08011ec0 + -1;
    if (*pcVar1 < '\0') {
      *pcVar1 = *(char *)(*DAT_08011ebc + 8) + -1;
    }
    *DAT_08011ec8 = *(int *)(*DAT_08011ebc + 4) + *DAT_08011ec0 * 0x18;
    *(char *)(*DAT_08011ebc + 9) = *(char *)(*DAT_08011ebc + 9) + -1;
    if (*(char *)(*DAT_08011ebc + 9) < '\0') {
      *(undefined1 *)(*DAT_08011ebc + 9) = 0;
    }
    if (*(byte *)(*DAT_08011ebc + 8) - 1 == (int)*DAT_08011ec0) {
      if (*(byte *)(*DAT_08011ebc + 8) < 2) {
        *(char *)(*DAT_08011ebc + 9) = *(char *)(*DAT_08011ebc + 8) + -1;
      }
      else {
        *(undefined1 *)(*DAT_08011ebc + 9) = 1;
      }
    }
    FUN_0800cac4(*DAT_08011ebc,*DAT_08011ec0);
  }
  else if (iVar3 == 2) {
    if (*DAT_08011ebc == DAT_08011ecc) goto LAB_08011e6c;
    FUN_0800b030();
  }
  iVar5 = *DAT_08011eb8;
  *DAT_08011eb8 = *DAT_08011eb8 + -1;
  if (-1 < iVar5) {
    return;
  }
LAB_08011e6c:
  *DAT_08011eb4 = '\0';
  if ((((*(int *)(*DAT_08011ec8 + 0xc) != 0) && (*(int *)(*DAT_08011ec8 + 0xc) != DAT_08011ed0)) &&
      (*(int *)(*DAT_08011ec8 + 0xc) != DAT_08011ed4)) &&
     (*(int *)(*DAT_08011ec8 + 0xc) != DAT_08011ed8)) {
    (**(code **)(*DAT_08011ec8 + 0xc))(1,*DAT_08011ec0);
  }
  FUN_0800ae2c();
  return;
}


/* 08011edc FUN_08011edc */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_08011edc(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  if ((*DAT_08011f38 & 0x1ff) == 0) {
    do {
      do {
        iVar3 = *DAT_08011f3c;
      } while (iVar3 != *DAT_08011f3c);
    } while (*DAT_08011f40 < _DAT_e000e018);
    uVar2 = (uint)((ulonglong)*DAT_08011f44 * 1000);
    iVar1 = FUN_080052f0(uVar2 - _DAT_e000e018,
                         (int)((ulonglong)*DAT_08011f44 * 1000 >> 0x20) -
                         (uint)(uVar2 < _DAT_e000e018),*DAT_08011f44,0);
    iVar1 = iVar1 + iVar3 * 1000;
  }
  else {
    iVar1 = FUN_08011f48();
  }
  return iVar1;
}


/* 08011f48 FUN_08011f48 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_08011f48(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  
  if ((_DAT_e000e010 & 0x10000) != 0) {
    *DAT_08011f9c = 1;
  }
  iVar3 = *DAT_08011fa0;
  iVar4 = *DAT_08011f9c;
  uVar2 = (uint)((ulonglong)*DAT_08011fa4 * 1000);
  iVar1 = FUN_080052f0(uVar2 - _DAT_e000e018,
                       (int)((ulonglong)*DAT_08011fa4 * 1000 >> 0x20) -
                       (uint)(uVar2 < _DAT_e000e018),*DAT_08011fa4,0);
  return iVar1 + (iVar3 + iVar4) * 1000;
}


/* 08011fa8 FUN_08011fa8 */

undefined4 FUN_08011fa8(void)

{
  return *DAT_08011fb0;
}


/* 08011fb4 FUN_08011fb4 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_08011fb4(void)

{
  undefined2 uVar1;
  float fVar2;
  
  uVar1 = FUN_0800dec0(1);
  *(undefined2 *)(*DAT_080121a0 + 6) = uVar1;
  if ((*(byte *)(DAT_080121a4 + 0x1c) & 4) == 0) {
    uVar1 = FUN_0800dec0(0);
    *(undefined2 *)(*DAT_080121a0 + 2) = uVar1;
    FUN_0800df14(0);
    fVar2 = (float)FUN_08012450();
    *(char *)(*DAT_080121a0 + 8) = (char)(int)fVar2;
  }
  if ((*(char *)(*DAT_080121a0 + 8) < 'Q') &&
     (*(char *)(*DAT_080121a0 + 8) + 0x28 < 0 == SCARRY4((int)*(char *)(*DAT_080121a0 + 8),0x28))) {
    if (-1 < *(int *)(*DAT_080121a0 + 0x2c)) {
      *(int *)(*DAT_080121a0 + 0x2c) = *(int *)(*DAT_080121a0 + 0x2c) + -1;
    }
    if (((*(char *)(*DAT_080121a0 + 0x2a) != '\0') && (*(char *)(*DAT_080121a0 + 0x2a) != '\x05'))
       && (*(int *)(*_DAT_080121b0 + 0x10) != 9999)) {
      if (0 < *(int *)(*DAT_080121a0 + 0x30)) {
        *(int *)(*DAT_080121a0 + 0x30) = *(int *)(*DAT_080121a0 + 0x30) + -1;
      }
      if ((*(char *)(*DAT_080121a0 + 0x2a) == '\x01') && (*(int *)(*_DAT_080121b0 + 0x10) != 0)) {
        if (*(int *)(*DAT_080121a0 + 0x30) < 1) {
          FUN_0800f200(3);
          FUN_0800f808(3,s_ctrl_task_080121e4,s____src_app_src_ctrl_task_c_080121c8,DAT_080121c4,
                       0x23b,s_T12_STA_SLEEP_080121b3 + 1);
          FUN_0800e27c(4);
          FUN_0800f270(*(undefined4 *)(*_DAT_080121b0 + 0xc));
          FUN_0800ade4(*(undefined4 *)(*_DAT_080121b0 + 0x14));
        }
      }
      else if ((*(char *)(*DAT_080121a0 + 0x2a) == '\x03') &&
              (*(int *)(*_DAT_080121b0 + 0x14) != 9999)) {
        if (*(int *)(*DAT_080121a0 + 0x30) < 1) {
          FUN_0800f200(4);
          FUN_0800f270(0);
          FUN_0800f808(3,s_ctrl_task_080121e4,s____src_app_src_ctrl_task_c_080121c8,DAT_080121c4,
                       0x247,s_T12_STA_STANDBY_080121f0);
          FUN_0800e27c(4);
        }
      }
      else if ((((*(char *)(*DAT_080121a0 + 0x2a) == '\x04') ||
                (*(char *)(*DAT_080121a0 + 0x2a) == '\x02')) &&
               (*(int *)(*DAT_080121a0 + 0x24) < 0x32)) &&
              (*(char *)(*_DAT_080121b0 + 0x55) == '\x01')) {
        FUN_0800f200(5);
        FUN_0800f808(3,s_ctrl_task_080121e4,s____src_app_src_ctrl_task_c_080121c8,DAT_080121c4,0x251
                     ,s_T12_STA_OFF_08012200);
      }
    }
    return;
  }
  *(uint *)(DAT_080121a4 + 0x1c) = *(uint *)(DAT_080121a4 + 0x1c) | 4;
  DataSynchronizationBarrier(0xf);
  *DAT_080121a8 = (*DAT_080121a8 & 0x700 | DAT_080121ac) + 4;
  DataSynchronizationBarrier(0xf);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}


/* 0801220c FUN_0801220c */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0801220c(void)

{
  uint uVar1;
  byte bVar2;
  undefined1 uVar3;
  undefined4 uVar4;
  int iVar5;
  uint in_fpscr;
  float fVar6;
  
  uVar3 = FUN_0800de6c();
  *(undefined1 *)(*DAT_08012350 + 0x29) = uVar3;
  uVar4 = FUN_0800deb4();
  *(undefined4 *)(*DAT_08012350 + 0x10) = uVar4;
  if ((*(byte *)(_DAT_08012354 + 0x1c) & 0x7f) == 0) {
    if (*(char *)(*DAT_08012350 + 0x29) == '\0') {
      FUN_0800ae84();
    }
    else {
      FUN_0800ade4(*(undefined4 *)(*DAT_08012394 + 0x10));
      FUN_0800af18();
    }
    if (*(char *)(*DAT_08012350 + 0x34) != '\0') {
      *(undefined1 *)(*DAT_08012350 + 0x34) = 0;
      iVar5 = *(int *)(*DAT_08012394 + 0x10);
      if (iVar5 < 3) {
        iVar5 = 2;
      }
      FUN_0800ade4(iVar5);
      FUN_0800af18();
    }
    if ((*(byte *)(_DAT_08012354 + 0x1c) & 0x7f) != 0) {
      *(undefined1 *)(*DAT_08012350 + 0x2b) = 0;
    }
    if (*(char *)(*DAT_08012350 + 0x2b) != '\x02') {
      fVar6 = (float)VectorSignedToFloat(*(undefined4 *)(*DAT_08012350 + 0x24),
                                         (byte)(in_fpscr >> 0x15) & 3);
      fVar6 = *(float *)(*DAT_08012398 + 0xb8) - fVar6;
      uVar1 = in_fpscr & 0xfffffff | (uint)(fVar6 < 0.0) << 0x1f | (uint)(fVar6 == 0.0) << 0x1e;
      bVar2 = (byte)(uVar1 >> 0x18);
      if ((bool)(bVar2 >> 6 & 1) || (bool)(bVar2 >> 7) != NAN(fVar6)) {
        fVar6 = (float)VectorSignedToFloat(*(undefined4 *)(*DAT_08012350 + 0x24),
                                           (byte)(uVar1 >> 0x15) & 3);
        fVar6 = -(*(float *)(*DAT_08012398 + 0xb8) - fVar6);
      }
      else {
        fVar6 = (float)VectorSignedToFloat(*(undefined4 *)(*DAT_08012350 + 0x24),
                                           (byte)(uVar1 >> 0x15) & 3);
        fVar6 = *(float *)(*DAT_08012398 + 0xb8) - fVar6;
      }
      if (fVar6 < 5.0) {
        if (*(char *)(*DAT_08012350 + 0x2b) == '\x01') {
          FUN_0800e27c(2);
        }
        *(undefined1 *)(*DAT_08012350 + 0x2b) = 2;
      }
    }
  }
  else if (*(char *)(*DAT_08012350 + 0x2a) != '\0') {
    FUN_0800f200(0);
    *(undefined1 *)(*DAT_08012350 + 0x28) = 0;
    FUN_0800f808(3,s_ctrl_task_08012388,s____src_app_src_ctrl_task_c_0801236c,DAT_08012368,0x1d7,
                 s_T12_STA_IDLE_08012357 + 1);
  }
  return;
}


/* 0801239c FUN_0801239c */

undefined1 FUN_0801239c(void)

{
  return *DAT_080123a4;
}


/* 080123a8 FUN_080123a8 */

undefined8 FUN_080123a8(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  undefined2 local_20;
  undefined1 local_1e;
  undefined1 uStack_1d;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 uStack_14;
  
  local_20 = (undefined2)param_1;
  local_1e = (undefined1)((uint)param_1 >> 0x10);
  uStack_1d = (undefined1)((uint)param_1 >> 0x18);
  local_1c = param_2;
  local_18 = param_3;
  uStack_14 = param_4;
  FUN_0800a2b4(5,1);
  FUN_080098b8(&local_20);
  local_20 = 0x6000;
  local_18 = 0;
  local_1c = CONCAT31(local_1c._1_3_,2);
  local_1e = 0x11;
  FUN_080096d0(DAT_08012410,&local_20);
  iVar2 = FUN_080098d0(DAT_08012410,0x2000);
  iVar3 = FUN_080098d0(DAT_08012410,0x4000);
  puVar1 = DAT_08012414;
  *DAT_08012414 = 0;
  if ((iVar2 == 0) && (iVar3 == 1)) {
    *puVar1 = 2;
  }
  else if ((iVar2 == 0) && (iVar3 == 0)) {
    *DAT_08012414 = 1;
  }
  return CONCAT44(local_1c,CONCAT13(uStack_1d,CONCAT12(local_1e,local_20)));
}


/* 08012418 FUN_08012418 */

void FUN_08012418(void)

{
  int iVar1;
  
  iVar1 = FUN_0800ed5c(*DAT_08012444 + 4,0x18);
  if (*(int *)*DAT_08012444 != iVar1) {
    *(int *)*DAT_08012444 = iVar1;
    FUN_08010230(DAT_0801244c,DAT_08012448,0x28);
  }
  return;
}


/* 08012450 FUN_08012450 */

float FUN_08012450(undefined4 param_1)

{
  undefined4 uVar1;
  uint in_fpscr;
  float fVar2;
  
  uVar1 = FUN_0800e0ec(param_1);
  fVar2 = (float)VectorUnsignedToFloat(uVar1,(byte)(in_fpscr >> 0x15) & 3);
  return fVar2 / 10.0;
}


/* 0801246c FUN_0801246c */

char FUN_0801246c(void)

{
  char cVar1;
  
  cVar1 = *(char *)(DAT_0801247c + 6);
  if (cVar1 != '\x01') {
    cVar1 = '\0';
  }
  return cVar1;
}


/* 08012480 FUN_08012480 */

undefined4 FUN_08012480(void)

{
  undefined4 uVar1;
  
  uVar1 = 6;
  switch(*(undefined1 *)(*DAT_080124b8 + 0x2c)) {
  case 0:
    uVar1 = 6;
    break;
  case 1:
    uVar1 = 5;
    break;
  case 2:
  case 3:
    uVar1 = 4;
    break;
  case 4:
  case 5:
    uVar1 = 2;
    break;
  case 6:
  case 7:
    uVar1 = 1;
  }
  return uVar1;
}


/* 080124bc FUN_080124bc */

undefined4 FUN_080124bc(float *param_1)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  if (*(char *)(param_1 + 0x11) == '\0') {
    uVar1 = 0;
  }
  else {
    fVar2 = *(float *)param_1[8];
    fVar3 = *(float *)param_1[10] - fVar2;
    fVar4 = fVar2 - param_1[0xd];
    fVar5 = 1.0;
    if ((param_1[0x12] < param_1[0x13]) && (param_1[0x13] != 0.0)) {
      fVar5 = (float)FUN_0800abd8(fVar3,param_1[0x13],param_1[0x12]);
    }
    if (((param_1[0x14] <= param_1[0xc]) && (0.0 < fVar3)) ||
       ((param_1[0xc] <= -param_1[0x14] && (fVar3 < 0.0)))) {
      fVar5 = DAT_08012668;
    }
    param_1[0xc] = param_1[0xc] + param_1[4] * fVar3 * fVar5;
    if (*(char *)((int)param_1 + 0x45) == '\0') {
      param_1[0xc] = param_1[0xc] - param_1[3] * fVar4;
    }
    if (param_1[0xc] <= param_1[0x10]) {
      if (param_1[0xc] < param_1[0xf]) {
        param_1[0xc] = param_1[0xf];
      }
    }
    else {
      param_1[0xc] = param_1[0x10];
    }
    fVar5 = DAT_08012668;
    if (*(char *)((int)param_1 + 0x45) != '\0') {
      fVar5 = param_1[3] * fVar3;
    }
    fVar5 = (param_1[0xc] - param_1[5] * fVar4) + fVar5;
    if (fVar5 <= param_1[0x10]) {
      if (fVar5 < param_1[0xf]) {
        fVar5 = param_1[0xf];
      }
    }
    else {
      fVar5 = param_1[0x10];
    }
    *(float *)param_1[9] = fVar5;
    *param_1 = param_1[3] * fVar3;
    param_1[1] = param_1[0xc];
    param_1[2] = -param_1[5] * fVar4;
    param_1[0xd] = fVar2;
    uVar1 = 1;
  }
  return uVar1;
}


/* 0801266c FUN_0801266c */

void FUN_0801266c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  undefined4 extraout_s6;
  undefined4 extraout_s7;
  undefined4 extraout_s8;
  
  *(undefined4 *)(param_1 + 0x24) = param_3;
  *(undefined4 *)(param_1 + 0x20) = param_2;
  *(undefined4 *)(param_1 + 0x28) = param_4;
  *(undefined1 *)(param_1 + 0x44) = 1;
  *(undefined4 *)(param_1 + 0x48) = DAT_080126d4;
  *(undefined4 *)(param_1 + 0x4c) = DAT_080126d4;
  FUN_08012746(DAT_080126d4,DAT_080126d8,param_1);
  *(undefined4 *)(param_1 + 0x38) = 100;
  FUN_080126dc(param_1,param_6);
  FUN_08012820(extraout_s6,extraout_s7,extraout_s8,param_1,param_5);
  return;
}


/* 080126dc FUN_080126dc */

void FUN_080126dc(int param_1,int param_2)

{
  if ((*(char *)(param_1 + 0x44) != '\0') && (*(int *)(param_1 + 0x18) != param_2)) {
    *(float *)(param_1 + 0xc) = DAT_0801271c - *(float *)(param_1 + 0xc);
    *(float *)(param_1 + 0x10) = DAT_0801271c - *(float *)(param_1 + 0x10);
    *(float *)(param_1 + 0x14) = DAT_0801271c - *(float *)(param_1 + 0x14);
  }
  *(int *)(param_1 + 0x18) = param_2;
  return;
}


/* 08012720 FUN_08012720 */

void FUN_08012720(int param_1,int param_2)

{
  if ((param_2 == 1) && (*(char *)(param_1 + 0x44) == '\0')) {
    FUN_0800999c(param_1);
  }
  *(bool *)(param_1 + 0x44) = param_2 == 1;
  return;
}


/* 08012746 FUN_08012746 */

void FUN_08012746(float param_1,float param_2,int param_3)

{
  if (param_1 < param_2) {
    *(float *)(param_3 + 0x3c) = param_1;
    *(float *)(param_3 + 0x40) = param_2;
    *(float *)(param_3 + 0x50) = param_2 * 1.0;
    if (*(char *)(param_3 + 0x44) != '\0') {
      if (**(float **)(param_3 + 0x24) <= *(float *)(param_3 + 0x40)) {
        if (**(float **)(param_3 + 0x24) < *(float *)(param_3 + 0x3c)) {
          **(undefined4 **)(param_3 + 0x24) = *(undefined4 *)(param_3 + 0x3c);
        }
      }
      else {
        **(undefined4 **)(param_3 + 0x24) = *(undefined4 *)(param_3 + 0x40);
      }
      if (*(float *)(param_3 + 0x40) < *(float *)(param_3 + 0x30)) {
        *(undefined4 *)(param_3 + 0x30) = *(undefined4 *)(param_3 + 0x40);
      }
      else if (*(float *)(param_3 + 0x30) < *(float *)(param_3 + 0x3c)) {
        *(undefined4 *)(param_3 + 0x30) = *(undefined4 *)(param_3 + 0x3c);
      }
    }
  }
  return;
}


/* 080127e4 FUN_080127e4 */

void FUN_080127e4(int param_1,int param_2)

{
  uint in_fpscr;
  float fVar1;
  float fVar2;
  
  if (0 < param_2) {
    fVar2 = (float)VectorUnsignedToFloat
                             (*(undefined4 *)(param_1 + 0x38),(byte)(in_fpscr >> 0x15) & 3);
    fVar1 = (float)VectorSignedToFloat(param_2,(byte)(in_fpscr >> 0x15) & 3);
    *(float *)(param_1 + 0x10) = *(float *)(param_1 + 0x10) * (fVar1 / fVar2);
    *(float *)(param_1 + 0x14) = *(float *)(param_1 + 0x14) / (fVar1 / fVar2);
    *(int *)(param_1 + 0x38) = param_2;
  }
  return;
}


/* 08012820 FUN_08012820 */

void FUN_08012820(float param_1,float param_2,float param_3,int param_4,int param_5)

{
  uint in_fpscr;
  float fVar1;
  
  if (((0.0 <= param_1) && (0.0 <= param_2)) && (0.0 <= param_3)) {
    *(bool *)(param_4 + 0x45) = param_5 != 0;
    fVar1 = (float)VectorUnsignedToFloat
                             (*(undefined4 *)(param_4 + 0x38),
                              (byte)((in_fpscr & 0xfffffff) >> 0x15) & 3);
    fVar1 = fVar1 / DAT_080128ac;
    *(float *)(param_4 + 0xc) = param_1;
    *(float *)(param_4 + 0x10) = param_2 * fVar1;
    *(float *)(param_4 + 0x14) = param_3 / fVar1;
    if (*(int *)(param_4 + 0x18) == 1) {
      *(float *)(param_4 + 0xc) = DAT_080128b0 - *(float *)(param_4 + 0xc);
      *(float *)(param_4 + 0x10) = DAT_080128b0 - *(float *)(param_4 + 0x10);
      *(float *)(param_4 + 0x14) = DAT_080128b0 - *(float *)(param_4 + 0x14);
    }
  }
  return;
}


/* 080128b4 FUN_080128b4 */

void FUN_080128b4(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  FUN_08012820(param_1,param_2,param_3,param_4,*(undefined1 *)(param_4 + 0x45));
  return;
}


/* 080128dc FUN_080128dc */

void FUN_080128dc(undefined4 param_1,undefined4 param_2,int param_3)

{
  *(undefined4 *)(param_3 + 0x4c) = param_1;
  *(undefined4 *)(param_3 + 0x48) = param_2;
  return;
}


/* 080128e8 FUN_080128e8 */

void FUN_080128e8(void)

{
  undefined2 *puVar1;
  int iVar2;
  
  if (*(char *)(DAT_08012a8c + 2) == '\0') {
    *DAT_08012a90 = *DAT_08012a90 + 1;
    switch(*DAT_08012a94) {
    case '\0':
      *DAT_08012a90 = 0;
      *DAT_08012a94 = *DAT_08012a94 + '\x01';
      break;
    case '\x01':
      iVar2 = FUN_08011fa8();
      if (0x640 < (uint)(iVar2 - *DAT_08012a98)) {
        *DAT_08012a94 = *DAT_08012a94 + '\x01';
        *DAT_08012a90 = 0;
        FUN_0800dcee(1);
      }
      break;
    case '\x02':
      if (*DAT_08012a90 < 500) {
        iVar2 = FUN_0800dec0(3);
        if ((8000 < iVar2) && (iVar2 < 0x2648)) {
          FUN_0800dcee(2);
          puVar1 = DAT_08012a8c;
          *DAT_08012a8c = 9000;
          puVar1[1] = 2000;
          *DAT_08012a94 = *DAT_08012a94 + '\x01';
          *DAT_08012a90 = 0;
        }
      }
      else {
        *DAT_08012a94 = '\x01';
        *DAT_08012a90 = 0;
        FUN_0800dcee();
        puVar1 = DAT_08012a8c;
        *DAT_08012a8c = 5000;
        puVar1[1] = 2000;
        *(undefined1 *)(puVar1 + 2) = 2;
        FUN_0800f808(3,s_QC_IO_08012ac8,s____src_drivers_src_qc_io_c_08012aac,DAT_08012aa8,0x8b,
                     s_QC9V_ERR__08012a9c);
      }
      break;
    case '\x03':
      if (*DAT_08012a90 < 500) {
        iVar2 = FUN_0800dec0(3);
        if (10000 < iVar2) {
          FUN_0800dcee(4);
          puVar1 = DAT_08012a8c;
          *DAT_08012a8c = 12000;
          puVar1[1] = 2000;
          *DAT_08012a94 = *DAT_08012a94 + '\x01';
          *DAT_08012a90 = 0;
        }
      }
      else {
        *DAT_08012a94 = *DAT_08012a94 + '\x01';
        *DAT_08012a90 = 0;
        FUN_0800f808(3,s_QC_IO_08012ac8,s____src_drivers_src_qc_io_c_08012aac,DAT_08012aa8,0xa0,
                     s_QC12V_ERR__08012ad0);
      }
      break;
    case '\x04':
      if (*DAT_08012a90 < 500) {
        iVar2 = FUN_0800dec0(3);
        if (19000 < iVar2) {
          *DAT_08012a94 = *DAT_08012a94 + '\x01';
          *DAT_08012a90 = 0;
          puVar1 = DAT_08012a8c;
          *DAT_08012a8c = 20000;
          puVar1[1] = 0x5dc;
        }
      }
      else {
        *DAT_08012a94 = *DAT_08012a94 + '\x01';
        *DAT_08012a90 = 0;
      }
      break;
    case '\x05':
      *DAT_08012a90 = 0;
      *(undefined1 *)(DAT_08012a8c + 2) = 1;
    }
  }
  return;
}


/* 08012adc FUN_08012adc */

undefined8 FUN_08012adc(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined2 local_18;
  undefined1 local_16;
  undefined1 local_15;
  undefined4 uStack_14;
  undefined4 local_10;
  undefined4 uStack_c;
  
  local_18 = (undefined2)param_1;
  local_16 = (undefined1)((uint)param_1 >> 0x10);
  local_15 = (undefined1)((uint)param_1 >> 0x18);
  uStack_14 = param_2;
  local_10 = param_3;
  uStack_c = param_4;
  FUN_0800a2b4(4,1);
  FUN_0800a2b4(8,1);
  local_18 = 3;
  local_10 = 1;
  local_15 = 0;
  local_16 = 0x11;
  FUN_080096d0(DAT_08012b40,&local_18);
  FUN_08005ffa(DAT_08012b40,3);
  local_18 = 0x300;
  local_10 = 1;
  FUN_080096d0(DAT_08012b44,&local_18);
  FUN_08005ffa(DAT_08012b44,0x300);
  FUN_08012da0();
  uVar1 = FUN_08011fa8();
  *DAT_08012b48 = uVar1;
  return CONCAT44(uStack_14,CONCAT13(local_15,CONCAT12(local_16,local_18)));
}


/* 08012b4c FUN_08012b4c */

undefined4 FUN_08012b4c(void)

{
  return DAT_08012b50;
}


/* 08012b54 FUN_08012b54 */

char FUN_08012b54(void)

{
  char cVar1;
  
  cVar1 = *(char *)(DAT_08012b64 + 4);
  if (cVar1 != '\x01') {
    cVar1 = '\0';
  }
  return cVar1;
}


/* 08012b68 FUN_08012b68 */

void FUN_08012b68(int param_1)

{
  if ((char)DAT_08012b94[2] != '\0') {
    if ((*DAT_08012b94 < 20000) && ((param_1 == 4 || (param_1 == 6)))) {
      param_1 = 2;
    }
    FUN_0800dcee(param_1);
  }
  return;
}


/* 08012b98 FUN_08012b98 */

int FUN_08012b98(void)

{
  return (int)*DAT_08012ba0;
}


/* 08012ba4 FUN_08012ba4 */

undefined4 FUN_08012ba4(void)

{
  int iVar1;
  int iVar2;
  
  *DAT_08012c50 = 0;
  iVar2 = 0;
  while( true ) {
    if (2 < iVar2) {
      FUN_0800a168(0x36,0xb6);
      FUN_0800f418(5);
      FUN_0800a168(0x36,0);
      FUN_0800f418(10);
      FUN_0800a168(0x11,0x80);
      FUN_0800a168(0x11,0x84);
      FUN_0800a168(0x4a,0x20);
      FUN_0800a168(0x56,1);
      FUN_0800a168(0x5f,0x80);
      FUN_0800f418(2);
      FUN_0800a168(0x5f,0);
      FUN_0800f418(10);
      FUN_0800a168(0xf,1);
      FUN_0800a168(0x10,0x61);
      FUN_0800a168(0x11,0x84);
      FUN_0800a168(0x21,3);
      FUN_0800f418(2);
      *DAT_08012c50 = 1;
      return 0;
    }
    iVar1 = FUN_0800a144(0);
    if (iVar1 != 0x90) break;
    iVar2 = iVar2 + 1;
  }
  return 0xffffffff;
}


/* 08012c54 FUN_08012c54 */

undefined4 FUN_08012c54(short *param_1)

{
  undefined4 uVar1;
  undefined4 local_10;
  undefined4 local_c;
  
  if (*DAT_08012cb0 == '\0') {
    uVar1 = 0xffffffff;
  }
  else {
    local_10 = 0;
    local_c = 0;
    FUN_0800a152(1,6,&local_10);
    *param_1 = (short)local_10 >> 2;
    param_1[1] = local_10._2_2_ >> 2;
    param_1[2] = (short)local_c >> 2;
    uVar1 = 0;
  }
  return uVar1;
}


/* 08012cb4 FUN_08012cb4 */

void FUN_08012cb4(void)

{
  int iVar1;
  
  iVar1 = FUN_0800ed5c(*DAT_08012ce4 + 4,8);
  if (*(int *)*DAT_08012ce4 != iVar1) {
    *(int *)*DAT_08012ce4 = iVar1;
    FUN_0801017e(0x3f,DAT_08012ce8,3);
  }
  return;
}


/* 08012cec FUN_08012cec */

undefined4 FUN_08012cec(void)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = *DAT_08012d54;
  piVar2 = (int *)(iVar3 + 0x18);
  uVar1 = 0;
  if (*(int *)(*DAT_08012d58 + 4) < *piVar2) {
    *(int *)(*DAT_08012d58 + 4) = *piVar2;
  }
  else if (*(int *)(*DAT_08012d58 + 4) < *(int *)(iVar3 + 0x1c)) {
    *(undefined4 *)(*DAT_08012d58 + 4) = *(undefined4 *)(iVar3 + 0x1c);
    uVar1 = 1;
  }
  else if (*(int *)(*DAT_08012d58 + 4) < *(int *)(iVar3 + 0x20)) {
    *(undefined4 *)(*DAT_08012d58 + 4) = *(undefined4 *)(iVar3 + 0x20);
    uVar1 = 2;
  }
  else if (*(int *)(iVar3 + 0x20) <= *(int *)(*DAT_08012d58 + 4)) {
    *(int *)(*DAT_08012d58 + 4) = *piVar2;
    uVar1 = 0;
  }
  return uVar1;
}


/* 08012d5c FUN_08012d5c */

void FUN_08012d5c(void)

{
  FUN_08005ffa(DAT_08012d6c,0x300);
  return;
}


/* 08012d70 FUN_08012d70 */

void FUN_08012d70(void)

{
  FUN_080098e2(DAT_08012d88,0x200);
  FUN_08005ffa(DAT_08012d88,0x100);
  return;
}


/* 08012d8c FUN_08012d8c */

void FUN_08012d8c(void)

{
  FUN_080098e2(DAT_08012d9c,0x300);
  return;
}


/* 08012da0 FUN_08012da0 */

void FUN_08012da0(void)

{
  FUN_080098e2(DAT_08012db4,1);
  FUN_08005ffa(DAT_08012db4,2);
  return;
}


/* 08012db8 FUN_08012db8 */

void FUN_08012db8(void)

{
  FUN_080098e2(DAT_08012dc4,3);
  return;
}


/* 08012dc8 FUN_08012dc8 */

undefined8 FUN_08012dc8(uint param_1,uint param_2)

{
  uint uVar1;
  undefined8 uVar2;
  
  uVar2 = FUN_08005b5a();
  uVar1 = (uint)uVar2;
  if (uVar1 != 0) {
    uVar1 = 1;
  }
  if ((int)(0x7ff00000 - ((uVar1 | (uint)((ulonglong)uVar2 >> 0x20)) & 0x7fffffff)) < 0) {
    if (param_1 != 0) {
      param_1 = 1;
    }
    if (-1 < (int)(0x7ff00000 - ((param_2 | param_1) & 0x7fffffff))) {
      FUN_0800ccf8(1);
    }
  }
  return uVar2;
}


/* 08012e38 FUN_08012e38 */

void FUN_08012e38(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  bool bVar5;
  
  FUN_08010100(DAT_08012f3c,DAT_08012f38,0x28);
  *DAT_08012f40 = DAT_08012f38 + 0x14;
  iVar1 = FUN_0800ed5c(*DAT_08012f40 + 4,0x18);
  bVar5 = *(int *)*DAT_08012f40 != iVar1;
  if (bVar5) {
    FUN_080053ee(*DAT_08012f40,DAT_08012f44,0x1c);
    uVar2 = FUN_0800ed5c(*DAT_08012f40 + 4,0x18);
    *(undefined4 *)*DAT_08012f40 = uVar2;
  }
  *DAT_08012f48 = DAT_08012f38 + 0x30;
  iVar1 = FUN_0800ed5c(*DAT_08012f48 + 4,0x6c);
  if ((*(int *)*DAT_08012f48 != iVar1) || (*(short *)(*DAT_08012f48 + 4) != 0x6c)) {
    FUN_080053ee(*DAT_08012f48,DAT_08012f4c,0x70);
    uVar2 = FUN_0800ed5c(*DAT_08012f48 + 4,0x6c);
    *(undefined4 *)*DAT_08012f48 = uVar2;
    bVar5 = true;
  }
  if (bVar5) {
    FUN_08010230(DAT_08012f3c,DAT_08012f38,0x28);
  }
  FUN_0801011a(0x3f,DAT_08012f50,3);
  *DAT_08012f54 = DAT_08012f50;
  iVar1 = FUN_0800ed5c(*DAT_08012f54 + 4,8);
  if (*(int *)*DAT_08012f54 != iVar1) {
    puVar3 = (undefined4 *)*DAT_08012f54;
    uVar2 = DAT_08012f58[1];
    uVar4 = DAT_08012f58[2];
    *puVar3 = *DAT_08012f58;
    puVar3[1] = uVar2;
    puVar3[2] = uVar4;
    uVar2 = FUN_0800ed5c(*DAT_08012f54 + 4,8);
    *(undefined4 *)*DAT_08012f54 = uVar2;
    FUN_0801017e(0x3f,DAT_08012f50,3);
  }
  return;
}


/* 08012f5c FUN_08012f5c */

/* WARNING: Removing unreachable block (ram,0x08012fb2) */

void FUN_08012f5c(void)

{
  bool bVar1;
  undefined2 uVar2;
  int iVar3;
  uint in_fpscr;
  uint uVar4;
  undefined4 uVar5;
  float fVar6;
  
  switch(*(undefined1 *)*DAT_080132f4) {
  case 0:
    FUN_08013310(DAT_080132f8);
    *(undefined1 *)(*DAT_080132f4 + 1) = 0;
    *(undefined1 *)*DAT_080132f4 = 2;
  case 1:
    *(char *)(*DAT_080132f4 + 1) = *(char *)(*DAT_080132f4 + 1) + '\x01';
    *(undefined1 *)*DAT_080132f4 = 2;
  case 2:
    uVar2 = FUN_0800dec0(3);
    *(undefined2 *)*DAT_080132fc = uVar2;
    FUN_0800c714(*(undefined2 *)*DAT_080132fc);
    uVar2 = FUN_0800dec0(4);
    *(undefined2 *)(*DAT_080132fc + 4) = uVar2;
    FUN_0800c3cc(*(undefined2 *)(*DAT_080132fc + 4));
    uVar5 = VectorUnsignedToFloat((uint)*(ushort *)(*DAT_080132fc + 4),(byte)(in_fpscr >> 0x15) & 3)
    ;
    *(undefined4 *)(*DAT_080132f4 + 4) = uVar5;
    if ((*(byte *)(DAT_08013300 + 0x1c) & 1) == 0) {
      uVar4 = VectorFloatToUnsigned(*(undefined4 *)(*DAT_080132f4 + 4),3);
      uVar5 = FUN_0800cd74(uVar4 & 0xffff,*(undefined1 *)(*DAT_080132fc + 0x20));
      *(undefined4 *)(*DAT_080132f4 + 8) = uVar5;
      fVar6 = (float)VectorSignedToFloat((int)*(char *)(*DAT_080132fc + 8) -
                                         (int)*(char *)(*DAT_08013304 + 0x5a),
                                         (byte)(in_fpscr >> 0x15) & 3);
      *(float *)(*DAT_080132f4 + 8) = fVar6 + *(float *)(*DAT_080132f4 + 8);
      fVar6 = (float)VectorSignedToFloat(*(undefined4 *)(*DAT_08013304 + 0x24),
                                         (byte)(in_fpscr >> 0x15) & 3);
      *(float *)(*DAT_080132f4 + 8) = *(float *)(*DAT_080132f4 + 8) - fVar6;
      uVar5 = FUN_0800cf8c((int)*(float *)(*DAT_080132f4 + 8),*(undefined4 *)(*DAT_080132fc + 0x24),
                           (int)*(float *)(*DAT_080132f4 + 0xb8));
      *(undefined4 *)(*DAT_080132fc + 0x24) = uVar5;
    }
    else {
      *(undefined4 *)(*DAT_080132fc + 0x24) = 0;
    }
    *(undefined1 *)*DAT_080132f4 = 3;
  case 3:
    bVar1 = false;
    iVar3 = FUN_08010ce8();
    if (iVar3 == 0) {
      iVar3 = FUN_0801246c();
      if ((iVar3 != 0) || (iVar3 = FUN_08012b54(), iVar3 != 0)) {
        bVar1 = true;
      }
    }
    else {
      bVar1 = true;
    }
    if ((((*(char *)(*DAT_080132f4 + 2) == '\0') || ((*(byte *)(DAT_08013300 + 0x1c) & 0x7f) != 0))
        || (!bVar1)) ||
       ((*(int *)(*DAT_080132fc + 0xc) == 0 || (*(char *)(*DAT_080132f4 + 0xd5) == '\x01')))) {
      *(undefined1 *)*DAT_080132f4 = 5;
      *(undefined4 *)(*DAT_080132f4 + 200) = 0x32;
    }
    else {
      if (*(char *)(*DAT_080132f4 + 3) == '\0') {
        in_fpscr = in_fpscr & 0xfffffff |
                   (uint)(30.0 <= *(float *)(*DAT_080132f4 + 0xb8) - *(float *)(*DAT_080132f4 + 8))
                   << 0x1d;
        if ((byte)(in_fpscr >> 0x1d) == 0) {
          *(undefined4 *)(*DAT_080132f4 + 0xc0) = 0x14;
        }
        else {
          *(undefined4 *)(*DAT_080132f4 + 0xc0) = 100;
        }
        if (*(int *)(*DAT_080132f4 + 0x9c) != *(int *)(*DAT_080132f4 + 0xc0)) {
          FUN_080127e4(*DAT_080132f4 + 100,*(undefined4 *)(*DAT_080132f4 + 0xc0));
        }
        FUN_080124bc(*DAT_080132f4 + 100);
      }
      else {
        *(undefined4 *)(*DAT_080132f4 + 0xc0) = 0x14;
        FUN_080124bc(*DAT_080132f4 + 0xc);
      }
      fVar6 = (float)VectorUnsignedToFloat
                               (*(undefined4 *)(*DAT_080132f4 + 0xc0),(byte)(in_fpscr >> 0x15) & 3);
      *(int *)(*DAT_080132f4 + 0xc4) =
           (int)((DAT_08013308 + *(float *)(*DAT_080132f4 + 0xbc) * fVar6) / DAT_0801330c);
      if (*(int *)(*DAT_080132f4 + 0xc4) < 1) {
        *(undefined1 *)*DAT_080132f4 = 5;
      }
      else {
        uVar5 = VectorSignedToFloat((uint)*(ushort *)(*DAT_080132f4 + 0xcc) +
                                    (int)*(short *)(*DAT_080132f4 + 0xce),
                                    (byte)(in_fpscr >> 0x15) & 3);
        FUN_08013310(uVar5);
        *(undefined1 *)*DAT_080132f4 = 4;
        FUN_0800de78();
        *(undefined2 *)(*DAT_080132f4 + 0xd0) = 0;
      }
      *(char *)(*DAT_080132fc + 0x28) = (char)(int)*(float *)(*DAT_080132f4 + 0xbc);
      *(undefined4 *)(*DAT_080132f4 + 200) = *(undefined4 *)(*DAT_080132f4 + 0xc0);
    }
    break;
  case 4:
    *(int *)(*DAT_080132f4 + 0xc4) = *(int *)(*DAT_080132f4 + 0xc4) + -1;
    *(int *)(*DAT_080132f4 + 200) = *(int *)(*DAT_080132f4 + 200) + -1;
    if ((*(int *)(*DAT_080132f4 + 0xc4) == *(int *)(*DAT_080132f4 + 200)) &&
       (*(int *)(*DAT_080132f4 + 0xc4) < 2)) {
      *(undefined1 *)*DAT_080132f4 = 0;
    }
    else if (*(int *)(*DAT_080132f4 + 0xc4) < 0) {
      FUN_08013310(DAT_080132f8);
      *(undefined1 *)*DAT_080132f4 = 5;
    }
    FUN_0800c1cc();
    break;
  case 5:
    *(int *)(*DAT_080132f4 + 200) = *(int *)(*DAT_080132f4 + 200) + -1;
    if (*(int *)(*DAT_080132f4 + 200) < 2) {
      *(undefined1 *)*DAT_080132f4 = 0;
    }
  }
  return;
}


/* 08013310 FUN_08013310 */

void FUN_08013310(float param_1)

{
  uint uVar1;
  uint in_fpscr;
  float fVar2;
  undefined8 uVar3;
  undefined2 local_30;
  undefined2 local_2e;
  undefined2 local_2a;
  undefined2 local_28;
  
  FUN_0800a918(&local_30);
  if (0.0 < param_1) {
    uVar1 = in_fpscr & 0xfffffff | (uint)(param_1 < DAT_080133c0) << 0x1f;
    if (SUB41(uVar1 >> 0x1f,0) == (NAN(param_1) || NAN(DAT_080133c0))) {
      FUN_0800a804(0x40000000);
    }
    else {
      fVar2 = (float)VectorUnsignedToFloat(*DAT_080133c4,(byte)(uVar1 >> 0x15) & 3);
      uVar3 = FUN_08005854(param_1 * fVar2);
      FUN_080056fc((int)uVar3,(int)((ulonglong)uVar3 >> 0x20),(int)DAT_080133c8,
                   (int)((ulonglong)DAT_080133c8 >> 0x20));
      uVar1 = FUN_08005822();
      if (*DAT_080133c4 < uVar1) {
        uVar1 = *DAT_080133c4;
      }
      local_30 = 0x60;
      local_2e = 1;
      local_2a = (undefined2)uVar1;
      local_28 = 0;
      FUN_0800a8a4(0x40000000,&local_30);
      FUN_0800a84c(0x40000000);
    }
  }
  else {
    FUN_0800a804(0x40000000);
  }
  return;
}


/* 080133d0 FUN_080133d0 */

void FUN_080133d0(void)

{
  uint *puVar1;
  undefined2 local_34;
  undefined2 local_32;
  undefined2 local_2e;
  undefined2 local_2c;
  undefined2 local_24;
  undefined2 local_22;
  undefined2 local_20;
  undefined2 local_1e;
  undefined1 local_1c;
  undefined2 local_14;
  undefined1 local_12;
  undefined4 local_c;
  undefined4 local_8;
  
  FUN_0800a294(1);
  FUN_0800a2b4(5,1);
  FUN_080098b8(&local_14);
  local_14 = 1;
  local_c = 2;
  local_12 = 0x11;
  local_8 = 2;
  FUN_080096d0(DAT_08013498,&local_14);
  FUN_0800a92c(&local_24);
  puVar1 = DAT_080134a0;
  *DAT_080134a0 = *DAT_0801349c / 60000;
  local_20 = (undefined2)*puVar1;
  local_24 = 0;
  local_1e = 0;
  local_22 = 0;
  local_1c = 0;
  FUN_0800a94c(0x40000000,&local_24);
  FUN_0800a7ee(0x40000000);
  FUN_0800a918(&local_34);
  local_34 = 0x60;
  local_32 = 1;
  local_2e = 0;
  local_2c = 0;
  FUN_0800a8a4(0x40000000,&local_34);
  FUN_0800a83a(0x40000000);
  FUN_0800a828(0x40000000);
  FUN_0800a804(0x40000000);
  FUN_0800a84c(0x40000000);
  return;
}


/* 080134a4 FUN_080134a4 */

void FUN_080134a4(void)

{
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  short local_14 [8];
  
  FUN_0800a294(4,1);
  local_14[2] = 49999;
  local_14[0] = (short)((*DAT_08013520 >> 1) / DAT_08013524) + -1;
  local_14[3] = 0;
  local_14[1] = 0;
  FUN_0800a94c(DAT_08013528,local_14);
  FUN_0800a7ee(DAT_08013528,1);
  FUN_0800a816(DAT_08013528,1);
  local_18 = 0x1e;
  local_15 = 1;
  local_17 = 0;
  local_16 = 1;
  FUN_0800a180(&local_18);
  FUN_080135b8();
  FUN_0800a84c(DAT_08013528,1);
  return;
}


/* 0801352c FUN_0801352c */

void FUN_0801352c(void)

{
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  short local_14 [8];
  
  FUN_0800a294(8,1);
  local_14[2] = 999;
  local_14[0] = (short)((*DAT_080135a0 >> 1) / DAT_080135a4) + -1;
  local_14[3] = 0;
  local_14[1] = 0;
  FUN_0800a94c(DAT_080135a8,local_14);
  FUN_0800a7ee(DAT_080135a8,1);
  FUN_0800a816(DAT_080135a8,1);
  local_18 = 0x32;
  local_15 = 1;
  local_17 = 2;
  local_16 = 2;
  FUN_0800a180(&local_18);
  FUN_0800a84c(DAT_080135a8,1);
  return;
}


/* 080135ac FUN_080135ac */

void FUN_080135ac(undefined4 param_1)

{
  *DAT_080135b4 = param_1;
  return;
}


/* 080135b8 FUN_080135b8 */

void FUN_080135b8(void)

{
  int iVar1;
  
  iVar1 = DAT_080135c4;
  *(undefined1 *)(DAT_080135c4 + 1) = 0;
  *(undefined1 *)(iVar1 + 2) = 0;
  *(undefined1 *)(iVar1 + 3) = 0;
  return;
}


/* 080135c8 FUN_080135c8 */

void FUN_080135c8(undefined4 param_1)

{
  undefined4 local_28;
  undefined2 local_24;
  undefined2 local_22;
  undefined2 local_20;
  undefined2 local_1e;
  undefined2 local_1c;
  undefined2 local_18 [4];
  undefined4 local_10;
  undefined4 local_c;
  
  FUN_0800a2b4(4,1);
  FUN_0800a2b4(0x4000);
  FUN_080098b8(local_18);
  local_18[0] = 0x200;
  local_10 = 2;
  local_c = 4;
  FUN_080096d0(DAT_08013630,local_18);
  FUN_0800abae(&local_28);
  local_24 = 0;
  local_22 = 0;
  local_20 = 0;
  local_1c = 0;
  local_1e = 8;
  local_28 = param_1;
  FUN_0800aae8(DAT_08013634,&local_28);
  FUN_0800aab4(DAT_08013634,1);
  return;
}


/* 08013638 FUN_08013638 */

undefined8 FUN_08013638(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  if (*DAT_0801386c == '\0') {
    *DAT_0801386c = '\x01';
    *DAT_08013870 = 0x50;
    *DAT_08013874 = '\0';
    *DAT_08013878 = '\0';
    FUN_08010ef4(2);
    FUN_08010f08(2);
  }
  FUN_08011214(0,0,0xa0,0x28,0,param_2,param_3,param_4);
  if (*DAT_08013878 == '\0') {
    if (*DAT_08013874 == '\0') {
      FUN_080105a4(0xe,9,0x38,0x15,8,1,0x4dc,0x4dc);
      FUN_080105a4(0x5a,9,0x38,0x15,8,0,0x4dc,0x4dc);
      FUN_08011500(0x12,0xc,*(undefined4 *)
                             (DAT_08013880 + (uint)*(byte *)(*DAT_0801387c + 4) * 0xc + 4),
                   DAT_08013884,0,0x4dc);
      uVar4 = 0x4dc;
      uVar5 = 0;
      FUN_08011500(0x5e,0xc,*(undefined4 *)
                             (DAT_08013880 + (uint)*(byte *)(*DAT_0801387c + 4) * 0xc + 8),
                   DAT_08013884);
    }
    else {
      FUN_080105a4(0xe,9,0x38,0x15,8,0,0x4dc,0x4dc);
      FUN_080105a4(0x5a,9,0x38,0x15,8,1,0x4dc,0x4dc);
      FUN_08011500(0x12,0xc,*(undefined4 *)
                             (DAT_08013880 + (uint)*(byte *)(*DAT_0801387c + 4) * 0xc + 4),
                   DAT_08013884,0x4dc,0);
      uVar4 = 0;
      uVar5 = 0x4dc;
      FUN_08011500(0x5e,0xc,*(undefined4 *)
                             (DAT_08013880 + (uint)*(byte *)(*DAT_0801387c + 4) * 0xc + 8),
                   DAT_08013884);
    }
  }
  else {
    uVar5 = 0x4dc;
    uVar4 = DAT_08013884;
    FUN_080115a0(0,0xc,0xa0,*(undefined4 *)(DAT_08013880 + (uint)*(byte *)(*DAT_0801387c + 4) * 0xc)
                 ,DAT_08013884,0x4dc,0);
  }
  iVar1 = FUN_08010f24();
  iVar2 = FUN_08010f34();
  iVar3 = iVar2;
  if (*(char *)(*DAT_08013888 + 0x52) != '\0') {
    iVar3 = iVar1;
    iVar1 = iVar2;
  }
  if ((iVar1 != 0) || (iVar3 != 0)) {
    *DAT_08013870 = 0x50;
  }
  if (iVar1 == 1) {
    if (*DAT_08013878 == '\0') {
      *DAT_08013874 = '\0';
    }
LAB_08013848:
    iVar3 = *DAT_08013870;
    *DAT_08013870 = *DAT_08013870 + -1;
    if (-1 < iVar3) goto LAB_08013866;
  }
  else {
    if (iVar3 == 1) {
      if (*DAT_08013878 == '\0') {
        *DAT_08013874 = '\x01';
      }
      goto LAB_08013848;
    }
    if ((iVar3 != 2) || (*DAT_08013878 != '\0')) goto LAB_08013848;
    if (*DAT_08013874 == '\x01') {
      *DAT_08013878 = '\x01';
      *DAT_08013870 = 0x1e;
      FUN_0800f070();
      FUN_08015dd8();
      FUN_080117d8();
      goto LAB_08013848;
    }
  }
  *DAT_0801386c = '\0';
  FUN_08014cd4(4);
LAB_08013866:
  return CONCAT44(uVar5,uVar4);
}


/* 0801388c FUN_0801388c */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_0801388c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  if (*DAT_08013a14 == '\0') {
    *DAT_08013a14 = '\x01';
    FUN_08010ef4(2);
    FUN_08010f08(2);
  }
  FUN_08011214(0,0,0xa0,0x28,0,param_2,param_3,param_4);
  FUN_080105a4(0,0,0xa0,0x28,0,0,0xffff,0xffff);
  if (((((_DAT_08013a18[0xe] & 2) == 0) && ((_DAT_08013a18[0xe] & 4) == 0)) &&
      ((_DAT_08013a18[0xe] & 8) == 0)) && ((_DAT_08013a18[0xe] & 0x20) == 0)) {
    uVar1 = *_DAT_08013a18;
    FUN_0800ad38(DAT_08013a24,s_T12__4d_08013a48,_DAT_08013a18[2]);
    FUN_080115a0(0,1,0xa0,DAT_08013a24,DAT_08013a44,0xffff,0);
    FUN_0800ad38(DAT_08013a24,s_IN__dV_NTC__2d_08013a50,uVar1 / 1000,(int)(char)_DAT_08013a18[4]);
    uVar5 = 0xffff;
    uVar4 = DAT_08013a44;
    FUN_080115a0(0,0x10,0xa0,DAT_08013a24,DAT_08013a44,0xffff,0);
    if (*(char *)((int)_DAT_08013a18 + 0x29) != '\0') {
      uVar4 = 8;
      uVar5 = 0xfc63;
      FUN_08011138(0x95,4,DAT_08013a60,8,8,0xfc63,0);
    }
  }
  else {
    FUN_0800ad38(DAT_08013a24,s_ERROR__08013a1b + 1);
    if ((_DAT_08013a18[0xe] & 2) != 0) {
      FUN_08005436(DAT_08013a24,&DAT_08013a28);
    }
    if ((_DAT_08013a18[0xe] & 4) != 0) {
      FUN_08005436(DAT_08013a24,&DAT_08013a2c);
    }
    if ((_DAT_08013a18[0xe] & 8) != 0) {
      FUN_08005436(DAT_08013a24,&DAT_08013a34);
    }
    if ((_DAT_08013a18[0xe] & 0x20) != 0) {
      FUN_08005436(DAT_08013a24,&DAT_08013a3c);
    }
    uVar5 = 0xf800;
    uVar4 = DAT_08013a44;
    FUN_080115a0(0,10,0xa0,DAT_08013a24,DAT_08013a44,0xf800,0);
  }
  iVar2 = FUN_08010f24();
  iVar3 = FUN_08010f34();
  if ((iVar2 == 1) && (iVar3 == 1)) {
    FUN_08014cd4(0);
    *DAT_08013a14 = '\0';
    *(undefined1 *)(*DAT_08013a64 + 5) = 0xaa;
    FUN_08012418();
  }
  return CONCAT44(uVar5,uVar4);
}


/* 08013a68 FUN_08013a68 */

undefined4 FUN_08013a68(void)

{
  return *(undefined4 *)(DAT_08013a70 + 4);
}


/* 08013a74 FUN_08013a74 */

void FUN_08013a74(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  if (*DAT_08013b68 == 0) {
    *DAT_08013b6c = 0;
    for (iVar2 = -0x27; iVar2 < 2; iVar2 = iVar2 + 2) {
      if (-1 < iVar2) {
        iVar2 = 0;
      }
      FUN_0801103a(0,(int)(short)iVar2,*(undefined2 *)(DAT_08013b70 + 8),
                   *(undefined2 *)(DAT_08013b70 + 10),DAT_08013b70 + 0xc,param_3,param_4);
      FUN_08011edc();
      FUN_08011400();
    }
    *DAT_08013b6c = 1;
    *DAT_08013b68 = 1;
    *DAT_08013b74 = 0;
  }
  else if (*DAT_08013b68 == 1) {
    iVar2 = *DAT_08013b74;
    *DAT_08013b74 = *DAT_08013b74 + 1;
    if (0x18 < iVar2) {
      *DAT_08013b68 = 3;
    }
  }
  if (*DAT_08013b68 == 3) {
    *DAT_08013b68 = 0;
    *DAT_08013b74 = 0;
    if ((*(byte *)(DAT_08013b78 + 0x1c) & 0x7f) == 0) {
      if (*(char *)(*DAT_08013bac + 0x50) == '\0') {
        FUN_08014cd4(1);
      }
      else {
        FUN_08014cd4(0xd);
      }
    }
    else {
      FUN_08014cd4(9);
      FUN_0800f808(3,s_ui_task_08013ba4,s____src_app_src_ui_task_c_08013b88,DAT_08013b84,0xfc,
                   s_war__x_08013b7c,*(undefined4 *)(DAT_08013b78 + 0x1c));
    }
  }
  iVar2 = FUN_08010f24();
  iVar1 = FUN_08010f34();
  if ((iVar2 == 1) && (iVar1 == 1)) {
    FUN_08014cd4(4);
    *(undefined4 *)(DAT_08013bb0 + 4) = 0;
    *DAT_08013b68 = 0;
  }
  return;
}


/* 08013bb4 FUN_08013bb4 */

void FUN_08013bb4(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint in_fpscr;
  float fVar6;
  undefined8 uVar7;
  uint local_40;
  uint local_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  
  local_38 = *DAT_08013fb8;
  uStack_34 = DAT_08013fb8[1];
  uStack_30 = DAT_08013fb8[2];
  uStack_2c = DAT_08013fb8[3];
  if (*DAT_08013fbc == '\0') {
    *DAT_08013fbc = '\x01';
    *DAT_08013fc0 = 0;
    fVar6 = (float)VectorSignedToFloat(*(undefined4 *)(*DAT_08013fc4 + 4),
                                       (byte)(in_fpscr >> 0x15) & 3);
    FUN_0800f270((int)fVar6);
    iVar1 = FUN_0800f0c4();
    if (iVar1 == 0) {
      FUN_0800f1cc(1);
    }
    FUN_0800f200(1);
    FUN_08010ef4(2);
    FUN_08010f08(2);
  }
  FUN_08011214(0,0,0xa0,0x28,0);
  FUN_08011138(0,0,DAT_08013fc8,0x25,0x28,0x2945,0);
  FUN_08011138(5,1,DAT_08013fcc,0x1c,8,0xc638,0x2945);
  uVar2 = FUN_08015da0(*(undefined4 *)(*DAT_08013fc4 + 4));
  FUN_0800ad38(DAT_08013fd4,&DAT_08013fd0,uVar2);
  FUN_08011500(3,0xc,DAT_08013fd4,DAT_08013fd8,0x4dc,0);
  local_40 = DAT_08013fb8[4];
  local_3c = DAT_08013fb8[5];
  iVar1 = FUN_080104e8();
  *(undefined2 *)((int)&local_40 + iVar1 * 2) = 0x4dc;
  FUN_08011500(4,0x1f,&DAT_08013fe0,DAT_08013fdc,local_40 & 0xffff,0);
  FUN_08011500(0x11,0x1f,&DAT_08013fe4,DAT_08013fdc,local_40 >> 0x10,0);
  FUN_08011500(0x1c,0x1f,&DAT_08013fe8,DAT_08013fdc,local_3c & 0xffff,0);
  uVar2 = FUN_08015da0(*(undefined4 *)(DAT_08013fec + 0x12));
  FUN_0800ad38(DAT_08013fd4,&DAT_08013fd0,uVar2);
  FUN_08011500(0x29,1,DAT_08013fd4,DAT_08013ff0,0xfc63,0);
  uVar2 = DAT_08013ffc;
  if (*(char *)(*DAT_08013ff4 + 0x51) != '\0') {
    uVar2 = DAT_08013ff8;
  }
  FUN_08011138(0x6f,0x12,uVar2,10,0xc,0xfc63,0);
  FUN_08011138(0x27,0x21,DAT_08014000,0x54,7,0x4dc,0);
  FUN_08010952(0x28,0x21,0x52,0xc638);
  FUN_08010952(0x28,0x27,0x52,0xc638);
  FUN_08010972(0x27,0x22,5,0xc638);
  FUN_08010972(0x7a,0x22,5,0xc638);
  uVar5 = (uint)((short)(ushort)(byte)DAT_08013fec[0x14] * 0x52) / 100;
  FUN_08011214(uVar5 + 0x28,0x23,0x52 - uVar5 & 0xffff,3,0);
  FUN_080105a4(0x7d,0,0x23,0xc,3,1,0x2945,0x2945);
  FUN_080105a4(0x7d,0xe,0x23,0xc,3,1,0x2945,0x2945);
  FUN_080105a4(0x7d,0x1c,0x23,0xc,3,1,0x2945,0x2945);
  FUN_0800ad38(DAT_08013fd4,&DAT_08014004,*DAT_08013fec / 1000);
  FUN_08011500(0x80,2,DAT_08013fd4,DAT_0801400c,0xc638,0x2945);
  fVar6 = (float)VectorSignedToFloat(*(undefined4 *)(DAT_08013fec + 8),(byte)(in_fpscr >> 0x15) & 3)
  ;
  uVar7 = FUN_08005854(fVar6 / DAT_08014010);
  FUN_0800ad38(DAT_08013fd4,s__3_1fA_08014014,(int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
  FUN_08011500(0x80,0xf,DAT_08013fd4,DAT_0801400c,0xc638,0x2945);
  FUN_0800ad38(DAT_08013fd4,&DAT_08014020,
               (int)((uint)*DAT_08013fec * *(int *)(DAT_08013fec + 8) + DAT_0801401c) /
               (DAT_0801401c << 1));
  FUN_08011500(0x80,0x1d,DAT_08013fd4,DAT_0801400c,0xc638,0x2945);
  if (*(char *)((int)DAT_08013fec + 0x29) != '\0') {
    FUN_08011138(0x73,1,DAT_08014028,8,8,0xfc63,0);
  }
  if (((char)DAT_08013fec[0x15] == '\0') && ((DAT_08013fec[0xe] & 0x7f) == 0)) {
    FUN_0800f200(1);
  }
  iVar3 = FUN_08010f24();
  iVar4 = FUN_08010f34();
  iVar1 = iVar4;
  if (*(char *)(*DAT_08013ff4 + 0x52) != '\0') {
    iVar1 = iVar3;
    iVar3 = iVar4;
  }
  if ((iVar3 == 1) && (iVar1 == 1)) {
    *(undefined4 *)(DAT_0801402c + 4) = 1;
    FUN_08014cd4(4);
    *DAT_08013fbc = '\0';
    FUN_0800f200();
  }
  else if (iVar1 == 2) {
    FUN_0800f200(2);
    FUN_08014cd4(10);
    *DAT_08013fbc = '\0';
  }
  else if (iVar3 == 2) {
    FUN_0800e27c(4);
    FUN_08012cec();
    fVar6 = (float)VectorSignedToFloat(*(undefined4 *)(*DAT_08013fc4 + 4),
                                       (byte)(in_fpscr >> 0x15) & 3);
    FUN_0800f270((int)fVar6);
    FUN_08012cb4();
  }
  else if ((iVar3 == 1) || (iVar1 == 1)) {
    FUN_08014cd4(3);
    *DAT_08013fbc = '\0';
  }
  if ((DAT_08013fec[0xe] & 0x7f) == 0) {
    if (((char)DAT_08013fec[0x15] == '\x03') || ((char)DAT_08013fec[0x15] == '\x04')) {
      FUN_08014cd4(10);
      *DAT_08013fbc = '\0';
    }
  }
  else {
    FUN_08014cd4(9);
    *DAT_08013fbc = '\0';
  }
  return;
}


/* 08014cd4 FUN_08014cd4 */

void FUN_08014cd4(undefined4 param_1)

{
  *DAT_08014cdc = param_1;
  return;
}


/* 08014ce0 FUN_08014ce0 */

void FUN_08014ce0(void)

{
  (**(code **)(DAT_08014cf8 + *DAT_08014cf4 * 4))();
  return;
}


/* 08014cfc FUN_08014cfc */

void FUN_08014cfc(void)

{
  undefined4 *puVar1;
  uint uVar2;
  
  puVar1 = DAT_08014d5c;
  if (*(char *)(*DAT_08014d58 + 5) == -0x56) {
    *DAT_08014d5c = 0;
    if (*(char *)(*DAT_08014d60 + 0x50) == '\0') {
      *puVar1 = 1;
      uVar2 = *(uint *)(DAT_08014d64 + 0x1c) & 0xffffff80;
      *(uint *)(DAT_08014d64 + 0x1c) = uVar2;
      if (uVar2 != 0) {
        *DAT_08014d5c = 9;
      }
    }
  }
  else {
    *DAT_08014d5c = 0xc;
  }
  FUN_080114f4(*(undefined1 *)(*DAT_08014d60 + 0x52));
  FUN_08011868();
  FUN_08010ef4(2);
  FUN_08010f08(2);
  return;
}


/* 08014d68 FUN_08014d68 */

void FUN_08014d68(void)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  short unaff_r4;
  char *unaff_r8;
  short sVar7;
  char cVar8;
  uint in_fpscr;
  float fVar9;
  char local_2c;
  char local_2b;
  char local_2a [6];
  
  cVar8 = '\0';
  if (*DAT_0801516c == '\0') {
    *DAT_0801516c = '\x01';
    *DAT_08015170 = 0x32;
    iVar2 = FUN_08015da0(*(undefined4 *)(*DAT_08015174 + 4));
    *DAT_08015178 = iVar2;
    FUN_0800f1cc(0);
    FUN_08010ef4(1);
    FUN_08010f08(1);
    *DAT_08015180 = *(char *)(*DAT_0801517c + 0x52) == '\0';
  }
  if (*(char *)(*DAT_0801517c + 0x52) != *DAT_08015180) {
    *DAT_08015180 = *(char *)(*DAT_0801517c + 0x52);
    FUN_08011214(0,0,0xa0,0x28,0);
    FUN_080105a4(0,0,0x26,0x14,3,1,0x2945,0x2945);
    FUN_08011138(6,6,DAT_08015184,0x1c,8,0xc638,0x2945);
  }
  FUN_08010952(0x1c,0x21,0x66,0xc638);
  FUN_08010952(0x1c,0x27,0x66,0xc638);
  FUN_08010972(0x1b,0x22,5,0xc638);
  FUN_08010972(0x82,0x22,5,0xc638);
  FUN_08011214(0x1c,0x22,0x66,5,0);
  iVar2 = FUN_08015da0(0x50);
  iVar6 = *DAT_08015178;
  iVar3 = FUN_08015da0(0x1c2);
  iVar4 = FUN_08015da0(0x50);
  FUN_08011214((((iVar6 - iVar2) * 0x62) / (iVar3 - iVar4) & 0xffU) + 0x1c,0x22,4,5,0x4dc);
  uVar5 = FUN_08015da0(0x50);
  FUN_0800ad38(DAT_0801518c,&DAT_08015188,uVar5);
  FUN_08011500(7,0x1e,DAT_0801518c,DAT_08015190,0xc638,0);
  uVar5 = FUN_08015da0(0x1c2);
  FUN_0800ad38(DAT_0801518c,&DAT_08015188,uVar5);
  FUN_08011500(0x86,0x1e,DAT_0801518c,DAT_08015190,0xc638,0);
  FUN_0800ad38(DAT_0801518c,&DAT_08015188,*DAT_08015178);
  FUN_08011500(0x29,0,DAT_0801518c,DAT_08015194,0xfc63,0);
  uVar5 = DAT_0801519c;
  if (*(char *)(*DAT_0801517c + 0x51) != '\0') {
    uVar5 = DAT_08015198;
  }
  FUN_08011138(0x6f,0x12,uVar5,10,0xc,0xfc63,0);
  iVar3 = FUN_08010f24();
  iVar4 = FUN_08010f34();
  iVar2 = iVar4;
  if (*(char *)(*DAT_0801517c + 0x52) != '\0') {
    iVar2 = iVar3;
    iVar3 = iVar4;
  }
  if ((iVar3 != 0) || (iVar2 != 0)) {
    *DAT_08015170 = 0x32;
  }
  if ((iVar3 != 1) || (iVar2 != 1)) {
    if (iVar3 == 1) {
      iVar2 = FUN_08015da0(0x50);
      cVar8 = iVar2 != *DAT_08015178;
      *DAT_08015178 = *DAT_08015178 - *(int *)(*DAT_0801517c + 8);
      iVar2 = FUN_08015da0(0x50);
      if (*DAT_08015178 < iVar2) {
        iVar2 = FUN_08015da0(0x50);
        *DAT_08015178 = iVar2;
      }
    }
    else if (iVar2 == 1) {
      iVar2 = FUN_08015da0(0x1c2);
      if (iVar2 != *DAT_08015178) {
        cVar8 = '\x02';
      }
      *DAT_08015178 = *(int *)(*DAT_0801517c + 8) + *DAT_08015178;
      iVar2 = FUN_08015da0(0x1c2);
      if (iVar2 < *DAT_08015178) {
        iVar2 = FUN_08015da0(0x1c2);
        *DAT_08015178 = iVar2;
      }
    }
    if (cVar8 != '\0') {
      FUN_0800ad38(&local_2c,&DAT_08015188,*DAT_08015178);
      if (*DAT_0801518c == local_2c) {
        if (DAT_0801518c[1] == local_2b) {
          if (DAT_0801518c[2] != local_2a[0]) {
            unaff_r4 = *DAT_08015194 * 2 + 0x29;
            unaff_r8 = local_2a;
          }
        }
        else {
          unaff_r4 = *DAT_08015194 + 0x29;
          unaff_r8 = &local_2b;
        }
      }
      else {
        unaff_r4 = 0x29;
        unaff_r8 = &local_2c;
      }
      sVar1 = 0x6a;
      sVar7 = unaff_r4;
      if (*(char *)(*DAT_0801517c + 0x52) != '\0') {
        sVar7 = 0x36;
        sVar1 = 0xa0 - unaff_r4;
      }
      if (cVar8 == '\x01') {
        FUN_080114d8(unaff_r4,0,(*DAT_08015194 * 3 - unaff_r4) + 0x2a,1);
        iVar2 = (uint)(ushort)DAT_08015194[1] * -2;
        do {
          FUN_08010f64((int)unaff_r4,0,0x6a,(int)DAT_08015194[1],1,1,0);
          FUN_08011500((int)unaff_r4,(int)(short)iVar2,unaff_r8,DAT_08015194,0xfc63,0);
          FUN_0801141c(sVar7,sVar1);
          iVar2 = iVar2 + 1;
        } while (iVar2 < 0);
        FUN_08011500((int)unaff_r4,0,unaff_r8,DAT_08015194,0xfc63,0);
        FUN_080114d8(0,0,0xa0,0x28);
      }
      else {
        FUN_080114d8(unaff_r4,DAT_08015194[1] + -1,(*DAT_08015194 * 3 - unaff_r4) + 0x2a,1);
        iVar2 = (uint)(ushort)DAT_08015194[1] << 1;
        do {
          FUN_08010f64((int)unaff_r4,0,0x6a,(int)DAT_08015194[1],0,1,0);
          FUN_08011500((int)unaff_r4,(int)(short)iVar2,unaff_r8,DAT_08015194,0xfc63,0);
          FUN_0801141c(sVar7,sVar1);
          iVar2 = iVar2 + -1;
        } while (0 < iVar2);
        FUN_08011500((int)unaff_r4,0,unaff_r8,DAT_08015244,0xfc63,0);
        FUN_080114d8(0,0,0xa0,0x28);
      }
    }
    iVar2 = *DAT_08015248;
    *DAT_08015248 = *DAT_08015248 + -1;
    if (-1 < iVar2) {
      return;
    }
  }
  iVar2 = FUN_08015da0(*(undefined4 *)(*DAT_0801524c + 4));
  if (iVar2 != *DAT_08015250) {
    if (*(char *)(*DAT_08015254 + 0x51) == '\0') {
      *(int *)(*DAT_0801524c + 4) = *DAT_08015250;
    }
    else {
      uVar5 = FUN_08015dc4(*DAT_08015250);
      *(undefined4 *)(*DAT_0801524c + 4) = uVar5;
    }
    fVar9 = (float)VectorSignedToFloat(*(undefined4 *)(*DAT_0801524c + 4),
                                       (byte)(in_fpscr >> 0x15) & 3);
    FUN_0800f270((int)fVar9);
    FUN_08012cb4();
  }
  FUN_08014cd4(1);
  *DAT_08015258 = 0;
  return;
}


/* 0801525c FUN_0801525c */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0801525c(void)

{
  char *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined4 local_2c;
  short local_28 [4];
  
  if (*DAT_08015540 == '\0') {
    *DAT_08015540 = '\x01';
    *DAT_08015544 = 100;
    *DAT_08015548 = '\0';
    *DAT_0801554c = '\0';
    FUN_08010ef4(2);
    FUN_08010f08(2);
  }
  FUN_08011214(0,0,0xa0,0x28,0);
  FUN_08011214(0,0,0xa0,0x14,0xfc63);
  FUN_080115a0(0,0,0xa0,*(int *)(DAT_08015558 + (uint)*(byte *)(*DAT_08015554 + 4) * 0x40 + 0xc) + 2
               ,DAT_08015550,0,0xfc63);
  iVar2 = *_DAT_0801555c;
  if (*(char *)(*_DAT_0801555c + 0x51) == '\0') {
    FUN_0800ad38(DAT_08015574,s__3d__3d__3d__C_08015578,*(undefined4 *)(iVar2 + 0x18),
                 *(undefined4 *)(iVar2 + 0x1c),*(undefined4 *)(iVar2 + 0x20));
  }
  else {
    uVar3 = FUN_08015da0(*(undefined4 *)(iVar2 + 0x20));
    uVar4 = FUN_08015da0(*(undefined4 *)(iVar2 + 0x1c));
    uVar5 = FUN_08015da0(*(undefined4 *)(iVar2 + 0x18));
    FUN_0800ad38(DAT_08015574,s__3d__3d__3d__F_0801555f + 1,uVar5,uVar4,uVar3);
  }
  FUN_080115a0(0,0x16,0xa0,DAT_08015574,DAT_0801558c,0x4dc,0);
  iVar2 = FUN_0800549e(DAT_08015574);
  local_28[0] = (short)(iVar2 * -8 + 0xa0U >> 1);
  local_28[1] = local_28[0] + 0x28;
  local_28[2] = local_28[0] + 0x50;
  local_2c = DAT_08015590;
  if (*DAT_08015548 == '\0') {
    FUN_08010952(local_28[*DAT_0801554c],0x27,*(undefined1 *)((int)&local_2c + (int)*DAT_0801554c),
                 0x4dc);
  }
  else if (*DAT_08015548 == '\x01') {
    FUN_08011294(local_28[*DAT_0801554c],0x16,*(undefined1 *)((int)&local_2c + (int)*DAT_0801554c),
                 0x10,0,0x4dc,0);
  }
  iVar6 = FUN_08010f24();
  iVar7 = FUN_08010f34();
  iVar2 = iVar7;
  if (*(char *)(*_DAT_0801555c + 0x52) != '\0') {
    iVar2 = iVar6;
    iVar6 = iVar7;
  }
  if ((iVar6 != 0) || (iVar2 != 0)) {
    *DAT_08015544 = 100;
  }
  if (iVar2 == 2) {
    if (*DAT_08015548 == '\0') {
      *DAT_08015548 = '\x01';
    }
    else if (*DAT_08015548 == '\x01') {
      *DAT_08015548 = '\0';
    }
  }
  pcVar1 = DAT_0801554c;
  if (iVar6 == 2) {
    if (*DAT_08015548 == '\0') goto LAB_08015528;
    if (*DAT_08015548 == '\x01') {
      *DAT_08015548 = '\0';
    }
  }
  else if (iVar2 == 1) {
    if (*DAT_08015548 == '\0') {
      *DAT_0801554c = (char)(*DAT_0801554c + 1) + (char)((*DAT_0801554c + 1) / 3) * -3;
    }
    else if ((*DAT_08015548 == '\x01') &&
            (*(int *)(*_DAT_0801555c + 0x18 + *DAT_0801554c * 4) =
                  *(int *)(*_DAT_0801555c + 0x18 + *DAT_0801554c * 4) + 10,
            0x1c2 < *(int *)(*_DAT_0801555c + 0x18 + *DAT_0801554c * 4))) {
      *(undefined4 *)(*_DAT_0801555c + 0x18 + *DAT_0801554c * 4) = 0x1c2;
    }
  }
  else if (iVar6 == 1) {
    if (*DAT_08015548 == '\0') {
      *DAT_0801554c = *DAT_0801554c + -1;
      if (*pcVar1 < '\0') {
        *pcVar1 = '\x02';
      }
    }
    else if ((*DAT_08015548 == '\x01') &&
            (*(int *)(*_DAT_0801555c + 0x18 + *DAT_0801554c * 4) =
                  *(int *)(*_DAT_0801555c + 0x18 + *DAT_0801554c * 4) + -10,
            *(int *)(*_DAT_0801555c + 0x18 + *DAT_0801554c * 4) < 0x50)) {
      *(undefined4 *)(*_DAT_0801555c + 0x18 + *DAT_0801554c * 4) = 0x50;
    }
  }
  iVar2 = *DAT_08015544;
  *DAT_08015544 = *DAT_08015544 + -1;
  if (-1 < iVar2) {
    return;
  }
LAB_08015528:
  FUN_0800f08c();
  *DAT_08015540 = '\0';
  FUN_08014cd4(4);
  return;
}


/* 08015594 FUN_08015594 */

void FUN_08015594(undefined4 param_1)

{
  FUN_080053ee(DAT_080155a4,param_1,0x1c);
  return;
}


/* 080155a8 FUN_080155a8 */

void FUN_080155a8(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 local_24 [3];
  
  if (*DAT_080156c4 == '\0') {
    *DAT_080156c4 = '\x01';
    *DAT_080156c8 = 100;
    FUN_08010ef4(2);
    FUN_08010f08(2);
  }
  FUN_08011214(0,0,0xa0,0x28,0);
  FUN_08011214(0,0,0xa0,0x14,0xfc63);
  FUN_080115a0(0,2,0xa0,*(int *)(DAT_080156d4 + (uint)*(byte *)(*DAT_080156d0 + 4) * 0x40 + 0x3c) +
                        3,DAT_080156cc,0,0xfc63);
  local_24[0] = *DAT_080156d8;
  local_24[1] = DAT_080156d8[1];
  local_24[2] = DAT_080156d8[2];
  FUN_0800ad38(DAT_080156fc,s_T90_s_V__1d__1d__1d_080156e4,local_24[*(byte *)(DAT_080156e0 + 0x20)],
               *(ushort *)(*DAT_080156dc + 4) / 100,
               ((uint)*(ushort *)(*DAT_080156dc + 4) % 100) / 10,
               (uint)*(ushort *)(*DAT_080156dc + 4) % 10);
  FUN_080115a0(0,0x16,0xa0,DAT_080156fc,DAT_08015700,0x4dc,0);
  iVar1 = FUN_08010f24();
  iVar2 = FUN_08010f34();
  iVar3 = iVar2;
  if (*(char *)(*DAT_080156dc + 0x52) != '\0') {
    iVar3 = iVar1;
    iVar1 = iVar2;
  }
  if (((iVar1 != 0) || (iVar3 != 0)) ||
     (iVar3 = *DAT_080156c8, *DAT_080156c8 = *DAT_080156c8 + -1, iVar3 < 0)) {
    *DAT_080156c4 = '\0';
    FUN_08014cd4(4);
  }
  return;
}


/* 08015704 FUN_08015704 */

void FUN_08015704(void)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  ushort *puVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint in_fpscr;
  float fVar9;
  float fVar10;
  undefined8 uVar11;
  
  if (*DAT_08015a98 == '\0') {
    *DAT_08015a98 = '\x01';
    FUN_08010ef4(2);
    FUN_08010f08(2);
  }
  FUN_08011214(0,0,0xa0,0x28,0);
  FUN_0801103a(2,2,0x22,0x12,DAT_08015a9c);
  FUN_080105a4(0x27,0,0x32,0xc,3,1,0x2945,0x2945);
  FUN_080105a4(0x27,0xe,0x32,0xc,3,1,0x2945,0x2945);
  FUN_080105a4(0x27,0x1c,0x32,0xc,3,1,0x2945,0x2945);
  FUN_080105a4(0x5b,0,0x45,0x28,3,1,0x2945,0x2945);
  uVar8 = *DAT_08015aa0 + 500 & 0xffff;
  iVar3 = FUN_0801246c();
  if (iVar3 == 0) {
    iVar3 = FUN_08012b54();
    if (iVar3 == 0) {
      FUN_08011138(6,0x18,DAT_08015ad0,0x1d,0xb,0x4dc,0);
    }
    else {
      puVar4 = (ushort *)FUN_08012b4c();
      uVar8 = (uint)*puVar4;
      FUN_08011138(6,0x18,DAT_08015acc,0x1d,0xb,0x4dc,0);
    }
    FUN_0800ad38(DAT_08015ab0,&DAT_08015aa8,uVar8 / 1000);
    FUN_08011500(0x33,2,DAT_08015ab0,DAT_08015ab4,0x4dc,0x2945);
    FUN_08011500(0x33,0xf,&DAT_08015ad4,DAT_08015ab4,0x4dc,0x2945);
    FUN_08011500(0x33,0x1d,&DAT_08015adc,DAT_08015ab4,0x4dc,0x2945);
  }
  else {
    iVar3 = FUN_0800eefc();
    uVar1 = *(ushort *)(iVar3 + 2);
    FUN_08011138(6,0x18,DAT_08015aa4,0x1d,0xb,0x4dc,0);
    FUN_0800ad38(DAT_08015ab0,&DAT_08015aa8,uVar1 / 1000);
    FUN_08011500(0x33,2,DAT_08015ab0,DAT_08015ab4,0x4dc,0x2945);
    iVar3 = FUN_0800eefc();
    uVar2 = *(ushort *)(iVar3 + 4);
    fVar9 = (float)VectorUnsignedToFloat((uint)uVar2,(byte)(in_fpscr >> 0x15) & 3);
    uVar11 = FUN_08005854(fVar9 / DAT_08015ab8);
    FUN_0800ad38(DAT_08015ab0,s__3_1fA_08015abc,(int)uVar11,(int)((ulonglong)uVar11 >> 0x20));
    FUN_08011500(0x33,0xf,DAT_08015ab0,DAT_08015ab4,0x4dc,0x2945);
    fVar9 = (float)VectorUnsignedToFloat((uint)uVar1,(byte)(in_fpscr >> 0x15) & 3);
    fVar10 = (float)VectorUnsignedToFloat((uint)uVar2,(byte)(in_fpscr >> 0x15) & 3);
    FUN_0800ad38(DAT_08015ab0,&DAT_08015ac4,(int)((fVar9 / DAT_08015ab8) * (fVar10 / DAT_08015ab8)))
    ;
    FUN_08011500(0x33,0x1d,DAT_08015ab0,DAT_08015ab4,0x4dc,0x2945);
  }
  FUN_08011138(0x5f,4,DAT_08015ae4,0x11,0xd,0xfc63,0x2945);
  FUN_08011138(0x60,0x17,DAT_08015ae8,0x11,0xd,0xfc63,0x2945);
  FUN_0800ad38(DAT_08015ab0,s__d__dV_08015aec,*DAT_08015aa0 / 1000,(*DAT_08015aa0 / 100) % 10);
  FUN_08011500(0x73,2,DAT_08015ab0,DAT_08015af4,0xfc63,0x2945);
  uVar11 = FUN_080057da(*(undefined4 *)(DAT_08015aa0 + 6));
  FUN_080056fc((int)uVar11,(int)((ulonglong)uVar11 >> 0x20),(int)DAT_08015af8,
               (int)((ulonglong)DAT_08015af8 >> 0x20));
  FUN_080058dc();
  uVar11 = FUN_08005854();
  FUN_0800ad38(DAT_08015ab0,s__3_1fR_08015b00,(int)uVar11,(int)((ulonglong)uVar11 >> 0x20));
  FUN_08011500(0x74,0x15,DAT_08015ab0,DAT_08015af4,0xfc63,0x2945);
  iVar3 = *(int *)(DAT_08015aa0 + 0x12);
  if ((DAT_08015aa0[0xe] & 0x7f) != 0) {
    iVar3 = (int)(char)DAT_08015aa0[4];
  }
  if (*(char *)(*DAT_08015b08 + 0x51) == '\0') {
    FUN_0800ad38(DAT_08015ab0,s__s_d_C_08015b1c,
                 *(undefined4 *)(DAT_08015b10 + (uint)*(byte *)(*DAT_08015b0c + 4) * 8 + 4),iVar3);
  }
  else {
    uVar5 = FUN_08015da0(iVar3);
    FUN_0800ad38(DAT_08015ab0,s__s_d_F_08015b14,
                 *(undefined4 *)(DAT_08015b10 + (uint)*(byte *)(*DAT_08015b0c + 4) * 8 + 4),uVar5);
  }
  iVar6 = FUN_08010f24();
  iVar7 = FUN_08010f34();
  iVar3 = iVar7;
  if (*(char *)(*DAT_08015b08 + 0x52) != '\0') {
    iVar3 = iVar6;
    iVar6 = iVar7;
  }
  if ((iVar6 != 0) || (iVar3 != 0)) {
    *DAT_08015a98 = '\0';
    FUN_08014cd4(4);
  }
  return;
}


/* 08015da0 FUN_08015da0 */

int FUN_08015da0(int param_1)

{
  if (*(char *)(*DAT_08015dc0 + 0x51) != '\0') {
    param_1 = (param_1 * 9) / 5 + 0x20;
  }
  return param_1;
}


/* 08015dc4 FUN_08015dc4 */

int FUN_08015dc4(int param_1)

{
  return ((param_1 + -0x20) * 5) / 9;
}


/* 08015dd8 FUN_08015dd8 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_08015dd8(void)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint in_fpscr;
  float fVar5;
  float fVar6;
  int iVar7;
  undefined4 local_24;
  undefined4 uStack_20;
  
  local_24 = *DAT_08015ebc;
  uStack_20 = DAT_08015ebc[1];
  uVar4 = (uint)*(ushort *)((int)&local_24 + (uint)*(byte *)(*DAT_08015ec0 + 0x20) * 2);
  iVar2 = *(int *)(*DAT_08015ec0 + 0xc) - uVar4;
  if (iVar2 + 0xfa < 0 != SCARRY4(iVar2,0xfa)) {
    uVar4 = *(uint *)(*DAT_08015ec0 + 0xc);
  }
  uVar3 = FUN_0800f154();
  fVar5 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x15) & 3);
  fVar5 = fVar5 / DAT_08015ec4;
  uVar3 = FUN_0800f0d0();
  fVar6 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x15) & 3);
  iVar2 = (int)(fVar5 * (fVar6 / DAT_08015ec4));
  fVar6 = (float)VectorSignedToFloat(uVar4,(byte)(in_fpscr >> 0x15) & 3);
  iVar7 = (int)((fVar5 * fVar5 * DAT_08015ec4) / fVar6);
  if (iVar7 < iVar2) {
    iVar2 = iVar7;
  }
  iVar7 = (iVar2 * 1000) / iVar7;
  if (1000 < iVar7) {
    iVar7 = 1000;
  }
  *(short *)(*_DAT_08015ec8 + 0xcc) = (short)((iVar7 * 0x5a) / 100);
  if (*(char *)(*DAT_08015ec0 + 0x20) == '\x02') {
    *(short *)(*_DAT_08015ec8 + 0xcc) = (short)iVar7;
  }
  *(undefined2 *)(*_DAT_08015ec8 + 0xce) = 0;
  uVar1 = FUN_0800f0d0();
  *(undefined2 *)(*_DAT_08015ec8 + 0xd2) = uVar1;
  return;
}

