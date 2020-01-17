#include <elf.h>
#include <stdio.h>
#include <string.h>

void print_ehdr(Elf64_Ehdr ehdr) {
  printf("============== ehdr ==================\n");
  printf("e_type=%d\n", ehdr.e_type);
  printf("e_machine=%d\n", ehdr.e_machine);
  printf("e_version=%d\n", ehdr.e_version);
  printf("e_entry=%ld\n", ehdr.e_entry);
  printf("e_phoff=%ld\n", ehdr.e_phoff);
  printf("e_shoff=%ld\n", ehdr.e_shoff);
  printf("e_flags=%d\n", ehdr.e_flags);
  printf("e_ehsize=%d\n", ehdr.e_ehsize);
  printf("e_phentsize=%d\n", ehdr.e_phentsize);
  printf("e_phnum=%d\n", ehdr.e_phnum);
  printf("e_shentsize=%d\n", ehdr.e_shentsize);
  printf("e_shnum=%d\n", ehdr.e_shnum);
  printf("e_shstrndx=%d\n", ehdr.e_shstrndx);
}

void print_shdr(Elf64_Shdr shdr) {
  printf("============== shdr ==================\n");
  printf("sh_name=%d\n", shdr.sh_name);
  printf("sh_type=%d\n", shdr.sh_type);
  printf("sh_flags=%ld\n", shdr.sh_flags);
  printf("sh_addr=%ld\n", shdr.sh_addr);
  printf("sh_offset=%ld\n", shdr.sh_offset);
  printf("sh_size=%ld\n", shdr.sh_size);
  printf("sh_link=%d\n", shdr.sh_link);
  printf("sh_info=%d\n", shdr.sh_info);
  printf("sh_addralign=%ld\n", shdr.sh_addralign);
  printf("sh_entsize=%ld\n", shdr.sh_entsize);
}

void print_phdr(Elf64_Phdr phdr) {
  printf("============== phdr ==================\n");
  printf("p_type=%d\n", phdr.p_type);
  printf("p_offset=%ld\n", phdr.p_offset);
  printf("p_vaddr=%ld\n", phdr.p_vaddr);
  printf("p_paddr=%ld\n", phdr.p_paddr);
  printf("p_filesz=%ld\n", phdr.p_filesz);
  printf("p_memz=%ld\n", phdr.p_memsz);
  printf("p_flags=%d\n", phdr.p_flags);
  printf("p_align=%ld\n", phdr.p_align);
}

void read_elf(const char* elfFile) {
  // switch to Elf32_Ehdr for x86 architecture.
  Elf64_Ehdr ehdr;
  Elf64_Shdr shdr;
  Elf64_Phdr phdr;
  Elf64_Sym  sym;
  Elf64_Rela rela;

  FILE* file = fopen(elfFile, "rb");
  if(file) {
    // read the ehdr
    fread(&ehdr, 1, sizeof(ehdr), file);

    // check so its really an elf file
    if (memcmp(ehdr.e_ident, ELFMAG, SELFMAG) == 0) {
       // this is a valid elf file
       print_ehdr(ehdr);

       fseek(file, ehdr.e_shoff, SEEK_END);
       fread(&shdr, 1, sizeof(shdr), file);
       print_shdr(shdr);

       fseek(file, ehdr.e_phoff, SEEK_SET);
       fread(&phdr, 1, sizeof(phdr), file);
       print_phdr(phdr);
    }

    // finally close the file
    fclose(file);
  }
}



int main() {
  read_elf("elf2");
}