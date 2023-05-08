#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <elf.h>

/**
 * is_elf - checks if a file is an ELF file.
 * @e_ident: pointer to the ELF magic numbers.
 *
 * Description: if file isn't ELF - exit code 98.
 */

void is_elf(unsigned char *e_ident)
{
	int i = 0;

	for (; i < 4; i++)
	{
		if (e_ident[i] != 127 && e_ident[i] != 'E' && e_ident[i] != 'L' && e_ident[i] != 'F')
		{
			dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
			exit(98);
		}
	}
}

/**
 * print_mgc - prints an ELF header's magic numbers.
 * @e_ident: pointer to the ELF magic numbers.
 */

void print_mgc(unsigned char *e_ident)
{
	int i = 0;

	printf(" Magic ");
	for (; i < EI_NIDENT; i++)
	{
		printf("%02x", e_ident[i]);
		if (i == EI_NIDENT - 1)
			printf("\n");
		else
			printf(" ");
	}
}

/**
 * print_class - prints an ELF header's class.
 * @e_ident: a pointer to an array containing the ELF class.
 */

void print_class(unsigned char *e_ident)
{
	printf(" Class: ");

	if (e_ident[EI_CLASS] == ELFCLASSNONE)
		printf("none\n");
	else if (e_ident[EI_CLASS] == ELFCLASS32)
		printf("ELF32\n");
	else if (e_ident[EI_CLASS] ==  ELFCLASS64)
		printf("ELF64\n");
	else
		printf("<unknown: %x>\n", e_ident[EI_CLASS]);
}

/**
 * print_data - prints an ELF headers's data.
 * @e_ident: pointer to an array containing the ELF class.
 */

void print_data(unsigned char *e_ident)
{
	printf(" Data: ");

	if (e_ident[EI_DATA] == ELFDATANONE)
		printf("none\n");
	else if (e_ident[EI_DATA] == ELFDATA2LSB)
		printf("2's complement, little endian\n");
	else if (e_ident[EI_DATA] == ELFDATA2MSB)
		printf("2's complement, big endian\n");
	else
		printf("<unknown: %x>\n", e_ident[EI_CLASS]);
}

/**
 * print_ver - prints an ELF header's version.
 * @e_ident: pointer to an array containing the ELF version.
 */

void print_ver(unsigned char *e_ident)
{
	printf(" Version: %d", e_ident[EI_VERSION]);

	if (e_ident[EI_VERSION] == EV_CURRENT)
		printf(" (current)\n");
	else
		printf("\n");
}

/**
 * print_os_abi - prints an ELF header's OS/ABI.
 * @e_ident: pointer to an array containing the ELF version.
 */

void print_os_abi(unsigned char *e_ident)
{
	printf(" OS/ABI: ");

	if (e_ident[EI_OSABI] == ELFOSABI_NONE)
		printf("UNIX - System V\n");
	else if (e_ident[EI_OSABI] == ELFOSABI_HPUX)
		printf("UNIX - HP-UX\n");
	else if (e_ident[EI_OSABI] == ELFOSABI_NETBSD)
		printf("UNIX - NetBSD\n");
	else if (e_ident[EI_OSABI] == ELFOSABI_LINUX)
		printf("UNIX - Linux\n");
	else if (e_ident[EI_OSABI] == ELFOSABI_SOLARIS)
		printf("UNIX - Solaris\n");
	else if (e_ident[EI_OSABI] == ELFOSABI_IRIX)
		printf("UNIX - IRIX\n");
	else if (e_ident[EI_OSABI] == ELFOSABI_FREEBSD)
		printf("UNIX - FreeBSD\n");
	else if (e_ident[EI_OSABI] == ELFOSABI_TRU64)
		printf("UNIX - TRU64\n");
	else if (e_ident[EI_OSABI] == ELFOSABI_ARM)
		printf("ARM\n");
	else if (e_ident[EI_OSABI] == ELFOSABI_STANDALONE)
		printf("Standalone App\n");
	else
		printf("<unknown: %x>\n", e_ident[EI_OSABI]);
}

/**
 * print_abi_ver - prints an ELF header's ABI version.
 * @e_ident: pointer to an array containing the ELF ABI veersion.
 */

void print_abi_ver(unsigned char *e_ident)
{
	printf(" ABI Version: %d\n", e_ident[EI_ABIVERSION]);
}

/**
 * print_type - prints an ELF header's type.
 * @e_type: the ELF type.
 * @e_ident: pointer to an array containing the ELF class.
 */

void print_type(unsigned int e_type, unsigned char *e_ident)
{
	if (e_ident[EI_DATA] == ELFDATA2MSB)
		e_type >>= 8;

	printf(" Type: ");

	if (e_type == ET_NONE)
		printf("NONE (None)\n");
	else if (e_type == ET_REL)
		printf("REL (Relocatable file)\n");
	else if (e_type == ET_EXEC)
		printf("EXEC (Executable file)\n");
	else if (e_type == ET_DYN)
		printf("DYN (Shared object file)\n");
	else if (e_type == ET_CORE)
		printf("CORE (Core file)\n");
	else
		printf("<unknown: %x>\n", e_type);
}

/**
 * print_entry - prints an ELF header's entry point.
 * @e_entry: address of the ELF entry point.
 * @e_ident: pointer to an array containing the ELF class.
 */

void print_entry(unsigned long int e_entry, unsigned char *e_ident)
{
	printf(" Entry point address: ");

	if (e_ident[EI_DATA] == ELFDATA2MSB)
	{
		e_entry = ((e_entry << 8) & 0xFF00FF00) | ((e_entry >> 8) & 0xFF00FF);
		e_entry = (e_entry << 16) | (e_entry >> 16);
	}

	if (e_ident[EI_CLASS] == ELFCLASS32)
		printf("%#x\n", (unsigned int)e_entry);
	else
		printf("%#lx\n", e_entry);
}

/**
 * close_elf - closes an ELF file.
 * @elf_dscr: ELF file descriptor.
 *
 * Description: if the file cannot be closed - exit code 98.
 */

void close_elf(int elf_dscr)
{
	if (close(elf_dscr) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", elf_dscr);
		exit(98);
	}
}

/**
 * main - displays the information contained in the ELF header at the start of an ELF file.
 * @argc: number of arguments supplied to main.
 * @agrv: an array of pointers to the arguments.
 *
 * Return: 0 on success.
 *
 * Description: if the file is not an ELF file or the function fails - exit code 98.
 */

int main(int __attribute__((__unused__)) argc, char *argv[])
{
	Elf64_Ehdr *header;
	int rd, fdscr = open(argv[1], O_RDONLY);

	if (fdscr == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		exit(98);
	}

	header = malloc(sizeof(Elf64_Ehdr));
	if (header == NULL)
	{
		close_elf(fdscr);
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		exit(98);
	}

	rd = read(fdscr, header, sizeof(Elf64_Ehdr));
	if (rd == -1)
	{
		free(header);
		close_elf(fdscr);
		dprintf(STDERR_FILENO, "Error: `%s`: No such file\n", argv[1]);
		exit(98);
	}

	is_elf(header->e_ident);
	printf("ELF Header:\n");
	print_mgc(header->e_ident);
	print_class(header->e_ident);
	print_data(header->e_ident);
	print_ver(header->e_ident);
	print_os_abi(header->e_ident);
	print_abi_ver(header->e_ident);
	print_type(header->e_type, header->e_ident);
	print_entry(header->e_entry, header->e_ident);

	free(header);
	close_elf(fdscr);
	return (0);
}
