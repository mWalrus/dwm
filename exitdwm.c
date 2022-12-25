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
	defined S_SHUTDOWN			|| \
	defined S_LOCK_ICON			|| \
	defined S_RESTART_DWM_ICON	|| \
	defined S_OFFSCREEN_ICON	|| \
	defined S_EXIT_ICON			|| \
	defined S_REBOOT_ICON		|| \
	defined S_SHUTDOWN_ICON		|| \
	defined S_FORMAT			|| \
	defined S_FORMAT_CLEAR
# error (conflicting macro names)
# endif

# define S_LOCK "lock"
# define S_RESTART_DWM "restart dwm"
# define S_OFFSCREEN "off-screen"
# define S_EXIT "exit"
# define S_REBOOT "reboot"
# define S_SHUTDOWN "shutdown"
# define S_LOCK_ICON "\uf023"			// <= FontAwesome icons
# define S_RESTART_DWM_ICON "\uf01e"
# define S_OFFSCREEN_ICON "\uf108"
# define S_EXIT_ICON "\uf2f5"
# define S_REBOOT_ICON "\uf021"
# define S_SHUTDOWN_ICON "\uf011"

# define S_FORMAT(ACTION) S_##ACTION##_ICON " " S_##ACTION
# define S_FORMAT_CLEAR "sed 's/^..//'"

	char command [150];

	sprintf(command,"echo  \"%s\n%s\n%s\n%s\n%s\n%s\" | dmenu -sb '%s' -nb '%s' -p exit: | %s",
		S_FORMAT (LOCK),
		S_FORMAT(RESTART_DWM),
		S_FORMAT (OFFSCREEN),
		S_FORMAT (EXIT),
		S_FORMAT (REBOOT),
		S_FORMAT (SHUTDOWN),
		col_mauve,
		col_gray1,
		S_FORMAT_CLEAR
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
# undef S_LOCK_ICON
# undef S_RESTART_DWM_ICON
# undef S_OFFSCREEN_ICON
# undef S_EXIT_ICON
# undef S_REBOOT_ICON
# undef S_SHUTDOWN_ICON
# undef S_FORMAT
# undef S_FORMAT_CLEAR
}
