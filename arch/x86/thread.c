#include <arch/x86/thread.h>
task_t* current_task;
task_t* first_task;
task_t* last_task;
int nTasks;
void switch_task(registers_t regs)
{
	
}
void create_task(task_t* task)
{
	if(nTasks == 0)
	{
		first_task = task;
		last_task = task;
		task->pid = 0;
		task->next = task;
		task->prev = NULL;
	}
	else {
		last_task->next = (struct sTask*)(task);
		task->prev = (struct sTask*)(last_task);
		last_task = task;
		task->next = first_task;
		task->pid = nTasks;
	}
	nTasks++;
}
