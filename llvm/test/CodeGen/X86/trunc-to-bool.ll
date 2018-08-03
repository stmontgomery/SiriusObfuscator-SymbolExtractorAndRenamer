; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; An integer truncation to i1 should be done with an and instruction to make
; sure only the LSBit survives. Test that this is the case both for a returned
; value and as the operand of a branch.
; RUN: llc < %s -mtriple=i686-unknown-linux-gnu | FileCheck %s

define zeroext i1 @test1(i32 %X)  nounwind {
; CHECK-LABEL: test1:
; CHECK:       # BB#0:
; CHECK-NEXT:    movb {{[0-9]+}}(%esp), %al
; CHECK-NEXT:    andb $1, %al
; CHECK-NEXT:    retl
    %Y = trunc i32 %X to i1
    ret i1 %Y
}

define i1 @test2(i32 %val, i32 %mask) nounwind {
; CHECK-LABEL: test2:
; CHECK:       # BB#0: # %entry
; CHECK-NEXT:    movl {{[0-9]+}}(%esp), %eax
; CHECK-NEXT:    movl {{[0-9]+}}(%esp), %ecx
; CHECK-NEXT:    btl %ecx, %eax
; CHECK-NEXT:    jae .LBB1_2
; CHECK-NEXT:  # BB#1: # %ret_true
; CHECK-NEXT:    movb $1, %al
; CHECK-NEXT:    retl
; CHECK-NEXT:  .LBB1_2: # %ret_false
; CHECK-NEXT:    xorl %eax, %eax
; CHECK-NEXT:    retl
entry:
    %shifted = ashr i32 %val, %mask
    %anded = and i32 %shifted, 1
    %trunced = trunc i32 %anded to i1
    br i1 %trunced, label %ret_true, label %ret_false
ret_true:
    ret i1 true
ret_false:
    ret i1 false
}

define i32 @test3(i8* %ptr) nounwind {
; CHECK-LABEL: test3:
; CHECK:       # BB#0:
; CHECK-NEXT:    movl {{[0-9]+}}(%esp), %eax
; CHECK-NEXT:    testb $1, (%eax)
; CHECK-NEXT:    je .LBB2_2
; CHECK-NEXT:  # BB#1: # %cond_true
; CHECK-NEXT:    movl $21, %eax
; CHECK-NEXT:    retl
; CHECK-NEXT:  .LBB2_2: # %cond_false
; CHECK-NEXT:    movl $42, %eax
; CHECK-NEXT:    retl
    %val = load i8, i8* %ptr
    %tmp = trunc i8 %val to i1
    br i1 %tmp, label %cond_true, label %cond_false
cond_true:
    ret i32 21
cond_false:
    ret i32 42
}

define i32 @test4(i8* %ptr) nounwind {
; CHECK-LABEL: test4:
; CHECK:       # BB#0:
; CHECK-NEXT:    testb $1, {{[0-9]+}}(%esp)
; CHECK-NEXT:    je .LBB3_2
; CHECK-NEXT:  # BB#1: # %cond_true
; CHECK-NEXT:    movl $21, %eax
; CHECK-NEXT:    retl
; CHECK-NEXT:  .LBB3_2: # %cond_false
; CHECK-NEXT:    movl $42, %eax
; CHECK-NEXT:    retl
    %tmp = ptrtoint i8* %ptr to i1
    br i1 %tmp, label %cond_true, label %cond_false
cond_true:
    ret i32 21
cond_false:
    ret i32 42
}

define i32 @test5(double %d) nounwind {
; CHECK-LABEL: test5:
; CHECK:       # BB#0:
; CHECK-NEXT:    pushl %eax
; CHECK-NEXT:    fldl {{[0-9]+}}(%esp)
; CHECK-NEXT:    fnstcw (%esp)
; CHECK-NEXT:    movzwl (%esp), %eax
; CHECK-NEXT:    movw $3199, (%esp) # imm = 0xC7F
; CHECK-NEXT:    fldcw (%esp)
; CHECK-NEXT:    movw %ax, (%esp)
; CHECK-NEXT:    fistps {{[0-9]+}}(%esp)
; CHECK-NEXT:    fldcw (%esp)
; CHECK-NEXT:    testb $1, {{[0-9]+}}(%esp)
; CHECK-NEXT:    je .LBB4_2
; CHECK-NEXT:  # BB#1: # %cond_true
; CHECK-NEXT:    movl $21, %eax
; CHECK-NEXT:    popl %ecx
; CHECK-NEXT:    retl
; CHECK-NEXT:  .LBB4_2: # %cond_false
; CHECK-NEXT:    movl $42, %eax
; CHECK-NEXT:    popl %ecx
; CHECK-NEXT:    retl
    %tmp = fptosi double %d to i1
    br i1 %tmp, label %cond_true, label %cond_false
cond_true:
    ret i32 21
cond_false:
    ret i32 42
}
