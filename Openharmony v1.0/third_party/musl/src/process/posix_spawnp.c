#include <spawn.h>
#include <unistd.h>
#include <unsupported_api.h>

int posix_spawnp(pid_t *restrict res, const char *restrict file,
	const posix_spawn_file_actions_t *fa,
	const posix_spawnattr_t *restrict attr,
	char *const argv[restrict], char *const envp[restrict])
{
	posix_spawnattr_t spawnp_attr = { 0 };
	unsupported_api(__FUNCTION__);
	if (attr) spawnp_attr = *attr;
	spawnp_attr.__fn = (void *)__execvpe;
	return posix_spawn(res, file, fa, &spawnp_attr, argv, envp);
}
