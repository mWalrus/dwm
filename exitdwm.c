# include <stdio.h>
# include <string.h>

void exitdwm ()
{
# if							   \
	defined S_LOCK				|| \
	defined S_RESTART_DWM		|| \
	defined S_OFFSCREEN			|| \
	defined S_EXIT				|| \
	defined S_REBOOT			|| \
	defined S_SHUTDOWN
# error (conflicting macro names)
# endif

# define S_LOCK "lock"
# define S_RESTART_DWM "restart dwm"
# define S_OFFSCREEN "off-screen"
# define S_EXIT "exit"
# define S_REBOOT "reboot"
# define S_SHUTDOWN "shutdown"

	int cmd_buf = 256;

	char command[cmd_buf];

	snprintf(command, cmd_buf, "echo  \"%s\n%s\n%s\n%s\n%s\n%s\" | dmenu -fn '%s' -sb '%s' -sf '%s' -nb '%s' -p exit: ",
		S_SHUTDOWN,
		S_REBOOT,
		S_LOCK,
		S_RESTART_DWM,
		S_OFFSCREEN,
		S_EXIT,
		dmenufont,
		col_mauve,
		col_black,
		col_gray1
	);

	FILE * exit_menu = popen(command, "r");

	char exit_action [16];

	if (
		exit_menu == NULL ||
		fscanf (exit_menu, "%15[a-zA-Z -]", exit_action) == EOF
	) {
		fputs ("Error. Failure in exit_dwm.", stderr);
		goto close_streams;
	}

	if (strcmp (exit_action, S_LOCK) == 0) system ("slock & sleep .5; xset dpms force off");
	else if (strcmp (exit_action, S_RESTART_DWM) == 0) quit (& (const Arg) {1});
	else if (strcmp (exit_action, S_OFFSCREEN) == 0) system ("sleep .5; xset dpms force off");
	else if (strcmp (exit_action, S_EXIT) == 0) quit (& (const Arg) {0});
	else if (strcmp (exit_action, S_REBOOT) == 0) system ("systemctl reboot");
	else if (strcmp (exit_action, S_SHUTDOWN) == 0) system ("systemctl poweroff -i");

close_streams:
	pclose (exit_menu);

# undef S_LOCK
# undef S_RESTART_DWM
# undef S_OFFSCREEN
# undef S_EXIT
# undef S_REBOOT
# undef S_SHUTDOWN
}
