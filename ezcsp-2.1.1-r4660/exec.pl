%
% By Marcello Balduccini [102208]
%
% Copyright (C) 2009-2018 Marcello Balduccini. All Rights Reserved.
%

%:- use_module(library(system)).
%:- use_module(library(timeout)).


batch(sicstus) :-
	use_module(library(system)),
	%nofileerrors,
	set_prolog_flag(fileerrors,off),
	nodebug,
	set_prolog_flag(unknown,fail),
	solve(S),
%	massage_solution(S,S2),
	S=S2,
%	\+ skip_solution(S2),
	\+ solution_exists(S2),
	output_assignments(S),
	halt.


batch(swiprolog) :-
	use_module(library(system)),
	%nofileerrors,
	set_prolog_flag(fileerrors,off),
	nodebug,
	set_prolog_flag(unknown,fail),
	solve(S),
%	massage_solution(S,S2),
	S=S2,
%	\+ skip_solution(S2),
	\+ solution_exists(S2),
	output_assignments(S),
	halt.


batch(bprolog) :-
	%nofileerrors,
	%set_prolog_flag(fileerrors,off),
	set_prolog_flag(debug,off),
	set_prolog_flag(unknown,fail),
	solve(S),
%	massage_solution(S,S2),
	S=S2,
%	\+ skip_solution(S2),
	\+ solution_exists(S2),
	output_assignments(S),
	halt.

%
% Additional equalities generated by clprq
% must be turned into (A,B) expressions
% to have a match with skip_solution/1.
%
solution_exists(S) :-
	skip_solution(E),
	term_to_string(S,X),
	term_to_string(E,X).

term_to_string(A,B) :-
	which_solver(bprolog),
	term2string(A,B).

term_to_string(A,B) :-
	which_solver(sicstus3),
	write_to_chars(A,B).

term_to_string(A,B) :-
	which_solver(sicstus4),
	write_to_codes(A,B).

term_to_string(A,B) :-
	which_solver(swiprolog),
% write_to_codes/2 is not available in all versions of SWI Prolog
%	write_to_codes(A,B).
	format(codes(B), '~w', [A]).

% [marcy 062711] Apparently no longer needed.
%
massage_solution([],[]).
massage_solution([A|ATail],[B|BTail]) :-
	A =.. [F|Args],
	F = '=',
	!,
	B =.. [','|Args],
	massage_solution(ATail,BTail).
massage_solution([A|ATail],[A|BTail]) :-
	massage_solution(ATail,BTail).

batch(_) :-  % batch must always succeed.
        write('++failed'),nl,
        halt. 

batch_to(bprolog,Timeout_Millisec) :-
	time_out(batch(bprolog), Timeout_Millisec, success),
	halt.

batch_to(sicstus,Timeout_Millisec) :-
	use_module(library(timeout)),
	time_out(user:batch(sicstus), Timeout_Millisec, success),
	halt.

batch_to(swiprolog,Timeout_Millisec) :-
	use_module(library(timeout)),
	time_out(user:batch(swiprolog), Timeout_Millisec, success),
	halt.

batch_to(_,_) :-  % batch must always succeed.
        write('++failed (TIMEOUT)'),nl,
        halt.

output_assignments([(ASPName,Var)|Tail]) :-
	!,
	write('++'),writeq(ASPName=Var),nl,
	output_assignments(Tail).

output_assignments([Exp|Tail]) :-
	write('++'),writeq(Exp),nl,
	output_assignments(Tail).

output_assignments([]) :-
	write('++succeeded'), nl.



/* Wrappers for certain global constraints */
prepare_disjoint2_list([],[],[],[],[]).
%
prepare_disjoint2_list([S1|S1t],[D1|D1t],[S2|S2t],[D2|D2t],[t(S1,D1,S2,D2)|Tail]) :-
	prepare_disjoint2_list(S1t,D1t,S2t,D2t,Tail).
%
disjoint2(L1,L2,L3,L4) :-
	prepare_disjoint2_list(L1,L2,L3,L4,Rectangles),
	disjoint2(Rectangles).
%
bp_prepare_disjoint2_list([],[],[],[],[]).
%
bp_prepare_disjoint2_list([S1|S1t],[D1|D1t],[S2|S2t],[D2|D2t],[[S1,S2,D1,D2]|Tail]) :-
	bp_prepare_disjoint2_list(S1t,D1t,S2t,D2t,Tail).
%
bp_disjoint2(L1,L2,L3,L4) :-
	bp_prepare_disjoint2_list(L1,L2,L3,L4,Rectangles),
	diffn(Rectangles).

get_tid(TID) :-
	curr_tid(TID),
	!.
get_tid(0).

set_tid(TID) :-
	retractall(curr_tid(_)),
	assert(curr_tid(TID)).

prepare_cumulative_list([],[],[],[]).
prepare_cumulative_list([S|St],[D|Dt],[R|Rt],[task(S,D,Q,R,TID)|Tail]) :-
	#=(Q,S+D),
	prepare_cumulative_list(St,Dt,Rt,Tail),
	get_tid(TID),
	TID2 is TID + 1,
	set_tid(TID2).
sics4_cumulative(St,Dur,Res,Max) :-
	prepare_cumulative_list(St,Dur,Res,Tasks),
	cumulative(Tasks,[limit(Max)]).

bp_cumulative([_],[_],[Res],Max) :-
	!,
	Res=<Max.
bp_cumulative(St,Dur,Res,Max) :-
	cumulative(St,Dur,Res,Max).
