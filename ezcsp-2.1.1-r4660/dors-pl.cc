char *dors_pl=(char *)
/* file automatically generated by fileToC.sh from dors.pl */
":- use_module(library(system)).\n"
":- use_module(library(fdbg)).\n"
"%:- fdbg_on([no_constraint_hook,labeling_hook(my_fdbg_label_show)]).\n"
"%:- fdbg_on([constraint_hook(my_fdbg_show),labeling_hook(my_fdbg_label_show)]).\n"
"%:- fdbg_on([no_constraint_hook,no_labeling_hook]).\n"
"\n"
"dors_store_fdvar_names([(ASPName,Var)|Mapping]) :-\n"
"	var(Var),\n"
"	!,\n"
"	fdbg_annotate(Var, fdvar(Name,_,_) , _),\n"
"	assert(varmap(Name,ASPName)),\n"
"	dors_store_fdvar_names(Mapping).\n"
"%\n"
"dors_store_fdvar_names([_|Mapping]) :-\n"
"	dors_store_fdvar_names(Mapping).\n"
"%\n"
"dors_store_fdvar_names([]) :-\n"
"	assert(choice_stack([])).\n"
"\n"
"get_fdvar_name(Var,Name) :-\n"
"	varmap(Var,Name),\n"
"	!.\n"
"%\n"
"get_fdvar_name(Var,Var).  % should never happen\n"
"\n"
"\n"
"show_stack :-\n"
"	!.	% skip the output below\n"
"%\n"
"show_stack :-\n"
"	choice_stack(Stack),\n"
"	length(Stack,N),\n"
"	write('stack: {'),\n"
"	write(N),\n"
"	write('} '),\n"
"	write(Stack),nl.\n"
"\n"
"dors_output_stack :-\n"
"	dors_prolog_stack_save(yes),\n"
"	dors_prolog_stack_save(file(F)),\n"
"	choice_stack(Stack),\n"
"	!,\n"
"	reverse(Stack,RevStack),\n"
"%	length(RevStack,N),\n"
"	( dors_prolog_stack_save_append(yes) ->\n"
"		Mode = append ; Mode = write\n"
"	),\n"
"	open(F,Mode,Stream),\n"
"	current_output(OldStream),\n"
"	set_output(Stream),\n"
"%	write('length: '),write(N),nl,\n"
"	writeq(RevStack),write('.'),nl,\n"
"	set_output(OldStream),\n"
"	close(Stream).\n"
"\n"
"dors_output_stack.\n"
"% when dors_prolog_stack_save(no)\n"
"\n"
"\n"
"dors_check_stack_dump(_,ASPOrderList) :-\n"
"	dors_prolog_stack_load(yes),\n"
"	dors_prolog_stack_load(file(F)),\n"
"	dors_prolog_stack_type(StackType),\n"
"	file_exists(F),\n"
"	!,\n"
"	seeing(OldStream),\n"
"	see(F),\n"
"	read(RevStack),\n"
"	seen,\n"
"	see(OldStream),\n"
"	revstack_to_asp_order_list(1,StackType,RevStack,ASPOrderList),\n"
"	assert(dors_stack(loaded)),\n"
"	assert(dors_stack_in(RevStack)),\n"
"	assert(dors_stack_type(StackType)),\n"
"write('using: '),write(ASPOrderList),nl.\n"
"%\n"
"dors_check_stack_dump(ASPOrderListFromProgram,ASPOrderListFromProgram) :-\n"
"	assert(dors_stack(from_program)),\n"
"% when dors_prolog_stack_load(no) or file does not exist\n"
"	!.\n"
"\n"
"revstack_to_asp_order_list(N,single,[bisect(Var,_,_)|RevStack],[(N,Var)|ASPOrderList]) :-\n"
"	N2 is N + 1,\n"
"	revstack_to_asp_order_list(N2,single,RevStack,ASPOrderList).\n"
"%\n"
"revstack_to_asp_order_list(N,merged,[Level|RevStack],ASPOrderList) :-\n"
"	N2 is N + 1,\n"
"	revstack_to_asp_order_list_aux(N,Level,LevelVars),\n"
"	revstack_to_asp_order_list(N2,merged,RevStack,PartialASPOrderList),\n"
"	append(LevelVars,PartialASPOrderList,ASPOrderList).\n"
"%\n"
"revstack_to_asp_order_list(_,_,[],[]).\n"
"%\n"
"revstack_to_asp_order_list_aux(N,[(bisect(Var,_,_),_)|Level],[(N,Var)|ASPOrderList]) :-\n"
"	revstack_to_asp_order_list_aux(N,Level,ASPOrderList).\n"
"%\n"
"revstack_to_asp_order_list_aux(N,[(bisect2(Var,_),_)|Level],[(N,Var)|ASPOrderList]) :-\n"
"	revstack_to_asp_order_list_aux(N,Level,ASPOrderList).\n"
"%\n"
"revstack_to_asp_order_list_aux(_,[],[]).\n"
"\n"
"inverse_entry(bisect(Var,=<,Val),bisect(Var,>,Val)).\n"
"inverse_entry(bisect(Var,=<,Val),bisect(Var,>=,Val2)) :-\n"
"	Val2 is Val + 1.\n"
"\n"
"inverse_entry(bisect(Var,<,Val),bisect(Var,>=,Val)).\n"
"inverse_entry(bisect(Var,<,Val),bisect(Var,>,Val2)) :-\n"
"	Val2 is Val - 1.\n"
"\n"
"inverse_entry(bisect(Var,>,Val),bisect(Var,=<,Val)).\n"
"inverse_entry(bisect(Var,>,Val),bisect(Var,<,Val2)) :-\n"
"	Val2 is Val + 1.\n"
"\n"
"inverse_entry(bisect(Var,>=,Val),bisect(Var,<,Val)).\n"
"inverse_entry(bisect(Var,>=,Val),bisect(Var,=<,Val2)) :-\n"
"	Val2 is Val - 1.\n"
"\n"
"to_stack0(Name,'$labeling_step'(X,Rel,Val,bisect)) :-\n"
"	to_stack(Name,'$labeling_step'(X,Rel,Val,bisect)).\n"
"\n"
"to_stack0(Name,forced(X,Rel,Val)) :-\n"
"	to_stack(Name,'$labeling_step'(X,Rel,Val,bisect)).\n"
"\n"
"to_stack0(Name,backtrack_from_forced(X,Rel,Val)) :-\n"
"	to_stack(Name,'$labeling_step'(X,Rel,Val,bisect)).\n"
"\n"
"to_stack(ASPName,'$labeling_step'(_,Rel,Val,bisect)) :-\n"
"	choice_stack([bisect(ASPName,Rel,Val)|_]),\n"
"	% just a change in the domain of the variable. No backtracking took place\n"
"	!.	%% needed because retract/1 is non-deterministic\n"
"%\n"
"%to_stack(ASPName) :-\n"
"%	choice_stack(Stack),\n"
"%	my_nth(Pos,Stack,ASPName),\n"
"%	!,\n"
"%	length(Stack,L_Stack),\n"
"%	L_Suffix is L_Stack - Pos,\n"
"%	length(Suffix,L_Suffix),\n"
"%	suffix(Suffix,Stack),\n"
"%	retract(choice_stack(Stack)),\n"
"%	assert(choice_stack([ASPName|Suffix])),\n"
"%show_stack,\n"
"%	!.	%% needed because retract/1 is non-deterministic\n"
"%%\n"
"to_stack(ASPName,'$labeling_step'(_,Rel,Val,bisect)) :-\n"
"	choice_stack(Stack),\n"
"	inverse_entry(bisect(ASPName,Rel,Val),InvEntry),\n"
"	my_nth(Pos,Stack,InvEntry),\n"
"	!,\n"
"	write('in backtrack of: '),write(bisect(ASPName,Rel,Val)),write('; '), write(InvEntry),write(' at pos '), write(Pos), nl,\n"
"	length(Stack,L_Stack),\n"
"	L_Suffix is L_Stack - Pos,\n"
"	length(Suffix,L_Suffix),\n"
"	suffix(Suffix,Stack),\n"
"	retract(choice_stack(Stack)),\n"
"write([bisect(ASPName,Rel,Val)|Suffix]),nl,\n"
"	assert(choice_stack([bisect(ASPName,Rel,Val)|Suffix])),\n"
"%	retract(choice_stack(Stack)),\n"
"%	assert(choice_stack([ASPName|Stack])),\n"
"show_stack,\n"
"	!.	%% needed because retract/1 is non-deterministic\n"
"to_stack(ASPName,'$labeling_step'(_,Rel,Val,bisect)) :-\n"
"	retract(choice_stack(Stack)),\n"
"	assert(choice_stack([bisect(ASPName,Rel,Val)|Stack])),\n"
"show_stack,\n"
"	!.	%% needed because retract/1 is non-deterministic\n"
"\n"
"% backtrack up to and INCLUDING ASPName\n"
"backtrack_stack(ASPName) :-\n"
"write('PROBLEM!!! backtrack_stack not properly implemented yet!!!'),nl.\n"
"%	choice_stack(Stack),\n"
"%	my_nth(Pos,Stack,ASPName),\n"
"%	!,\n"
"%	length(Stack,L_Stack),\n"
"%	L_Suffix is L_Stack - Pos,\n"
"%	length(Suffix,L_Suffix),\n"
"%	suffix(Suffix,Stack),\n"
"%	retract(choice_stack(Stack)),\n"
"%	assert(choice_stack(Suffix)),\n"
"%show_stack,\n"
"%	!.	%% needed because retract/1 is non-deterministic\n"
"\n"
"\n"
"\n"
"my_fdbg_show(Constraint, Actions) :-\n"
"	fdbg_annotate(Constraint, Actions, AnnotC, CVars),\n"
"	print(fdbg_output, AnnotC),\n"
"	nl(fdbg_output),\n"
"	fdbg_legend(CVars, Actions),\n"
"	nl(fdbg_output).\n"
"\n"
"my_fdbg_label_show(start, I, Var) :-\n"
"	fdbg_annotate(Var, AVar, _),\n"
"	( AVar = fdvar(NameX, _, Set)\n"
"	-> fdset_to_range(Set, Range),\n"
"	   get_fdvar_name(NameX,Name),\n"
"%to_stack(Name),\n"
"	   format(fdbg_output,\n"
"		  'Labeling [~p, <~p>]: starting in range ~p.~n',\n"
"		  [I,Name,Range])\n"
"	; format(fdbg_output,\n"
"		 'Labeling [~p, <>]: starting.~n',\n"
"		 [I])\n"
"	).\n"
"\n"
"my_fdbg_label_show(fail, I, Var) :-\n"
"	( var(Var)\n"
"	-> fdbg_annotate(Var, fdvar(NameX,_,_) , _),\n"
"	   get_fdvar_name(NameX,Name),\n"
"backtrack_stack(Name),\n"
"	   format(fdbg_output,\n"
"		  'Labeling [~p, <~p>]: failed.~n~n',\n"
"		  [I,Name])\n"
"	; format(fdbg_output,\n"
"		 'Labeling [~p, <>]: failed.~n~n',\n"
"		 [I])\n"
"	).\n"
"\n"
"my_fdbg_label_show(step(Step), I, Var) :-\n"
"	( var(Var)\n"
"	-> fdbg_annotate(Var, fdvar(NameX,_,_) , _),\n"
"	   get_fdvar_name(NameX,Name),\n"
"to_stack0(Name,Step),\n"
"write('fd_dom is '),fd_dom(Var,Dom),write(Dom),nl,\n"
"write('fd_min is '),fd_min(Var,Min),write(Min),nl,\n"
"write('fd_max is '),fd_max(Var,Max),write(Max),nl,\n"
"write('step is '),write(Step),nl,\n"
"	   format(fdbg_output,\n"
"		  'Labeling [~p, <~p>]: ~p~n~n',\n"
"		  [I,Name,Step])\n"
"	; \n"
"	format(fdbg_output,\n"
"		 'Labeling [~p, <>]: ~p~n~n',\n"
"		 [I,Step])\n"
"	).\n"
;
