; ModuleID = 'example/hello.c'
source_filename = "example/hello.c"
target datalayout = "e-m:e-i8:8:32-i16:16:32-i64:64-i128:128-n32:64-S128"
target triple = "aarch64-unknown-linux-gnu"

%struct.student = type { [50 x i8], [50 x i8], i32 }
%union.Data = type { i32, [16 x i8] }
%struct.my_struct = type { i32, [10 x i8], [25 x i8] }

@.str = private unnamed_addr constant [10 x i8] c"Orig: %s\0A\00", align 1
@.str.1 = private unnamed_addr constant [6 x i8] c"hello\00", align 1
@.str.2 = private unnamed_addr constant [12 x i8] c"output: %f\0A\00", align 1
@.str.3 = private unnamed_addr constant [12 x i8] c"%s, %s, %s\0A\00", align 1
@.str.4 = private unnamed_addr constant [21 x i8] c"pointer to my_struct\00", align 1
@.str.5 = private unnamed_addr constant [6 x i8] c"other\00", align 1
@.str.6 = private unnamed_addr constant [17 x i8] c"pointer to uchar\00", align 1
@.str.7 = private unnamed_addr constant [5 x i8] c"yes!\00", align 1
@.str.9 = private unnamed_addr constant [11 x i8] c"After: %s\0A\00", align 1
@.str.10 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

; Function Attrs: norecurse nounwind readnone
define dso_local double @func(i32 %0, double %1) local_unnamed_addr #0 {
  %3 = sitofp i32 %0 to double
  %4 = fmul double %3, %1
  %5 = fadd double %4, %3
  ret double %5
}

; Function Attrs: norecurse nounwind readnone
define dso_local double @foo(i32 %0, fp128 %1, %struct.student* nocapture readnone %2, %union.Data* nocapture readnone %3) local_unnamed_addr #0 {
  %5 = sitofp i32 %0 to fp128
  %6 = fmul fp128 %5, %1
  %7 = fadd fp128 %6, %5
  %8 = fptrunc fp128 %7 to double
  ret double %8
}

; Function Attrs: norecurse nounwind readnone
define dso_local i32 @bar(i32 %0) local_unnamed_addr #0 {
  %2 = mul nsw i32 %0, 3
  ret i32 %2
}

; Function Attrs: nounwind
define dso_local noalias i32* @foo2(i32 %0, %struct.my_struct* %1, i8* nocapture readnone %2, double (i32, double)* nocapture readnone %3) local_unnamed_addr #1 {
  %5 = getelementptr inbounds %struct.my_struct, %struct.my_struct* %1, i64 0, i32 1, i64 0
  %6 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i64 0, i64 0), i8* nonnull %5)
  tail call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull align 1 dereferenceable(6) %5, i8* nonnull align 1 dereferenceable(6) getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i64 0, i64 0), i64 6, i1 false) #4
  %7 = tail call noalias dereferenceable_or_null(4) i8* @malloc(i64 4) #4
  %8 = bitcast i8* %7 to i32*
  %9 = getelementptr inbounds %struct.my_struct, %struct.my_struct* %1, i64 0, i32 0
  %10 = load i32, i32* %9, align 4, !tbaa !2
  %11 = add nsw i32 %10, %0
  store i32 %11, i32* %8, align 4, !tbaa !7
  ret i32* %8
}

; Function Attrs: nofree nounwind
declare dso_local i32 @printf(i8* nocapture readonly, ...) local_unnamed_addr #2

; Function Attrs: argmemonly nounwind willreturn
declare void @llvm.lifetime.start.p0i8(i64 immarg, i8* nocapture) #3

; Function Attrs: nofree nounwind
declare dso_local noalias i8* @malloc(i64) local_unnamed_addr #2

; Function Attrs: argmemonly nounwind willreturn
declare void @llvm.lifetime.end.p0i8(i64 immarg, i8* nocapture) #3

; Function Attrs: nounwind
define dso_local i32 @main() local_unnamed_addr #1 {
  %1 = alloca %struct.my_struct, align 4
  %2 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([12 x i8], [12 x i8]* @.str.2, i64 0, i64 0), double 3.600000e+01)
  %3 = bitcast %struct.my_struct* %1 to i8*
  call void @llvm.lifetime.start.p0i8(i64 40, i8* nonnull %3) #4
  %4 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([12 x i8], [12 x i8]* @.str.3, i64 0, i64 0), i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.4, i64 0, i64 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.5, i64 0, i64 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.6, i64 0, i64 0))
  %5 = getelementptr inbounds %struct.my_struct, %struct.my_struct* %1, i64 0, i32 0
  store i32 10, i32* %5, align 4, !tbaa !2
  %6 = getelementptr inbounds %struct.my_struct, %struct.my_struct* %1, i64 0, i32 1, i64 0
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull align 4 dereferenceable(5) %6, i8* nonnull align 1 dereferenceable(5) getelementptr inbounds ([5 x i8], [5 x i8]* @.str.7, i64 0, i64 0), i64 5, i1 false) #4
  %7 = call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i64 0, i64 0), i8* nonnull %6) #4
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* nonnull align 4 dereferenceable(6) %6, i8* nonnull align 1 dereferenceable(6) getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i64 0, i64 0), i64 6, i1 false) #4
  %8 = load i32, i32* %5, align 4, !tbaa !2
  %9 = add nsw i32 %8, 15
  %10 = call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([11 x i8], [11 x i8]* @.str.9, i64 0, i64 0), i8* nonnull %6)
  %11 = call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([4 x i8], [4 x i8]* @.str.10, i64 0, i64 0), i32 %9)
  call void @llvm.lifetime.end.p0i8(i64 40, i8* nonnull %3) #4
  ret i32 0
}

; Function Attrs: argmemonly nounwind willreturn
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* noalias nocapture writeonly, i8* noalias nocapture readonly, i64, i1 immarg) #3

attributes #0 = { norecurse nounwind readnone "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="non-leaf" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "target-features"="+neon" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="non-leaf" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "target-features"="+neon" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nofree nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="non-leaf" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "target-features"="+neon" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind willreturn }
attributes #4 = { nounwind }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"Debian clang version 11.0.1-2"}
!2 = !{!3, !4, i64 0}
!3 = !{!"my_struct", !4, i64 0, !5, i64 4, !5, i64 14}
!4 = !{!"int", !5, i64 0}
!5 = !{!"omnipotent char", !6, i64 0}
!6 = !{!"Simple C/C++ TBAA"}
!7 = !{!4, !4, i64 0}
