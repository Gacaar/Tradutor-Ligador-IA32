#include <iostream>
#include <string>
#include <elfio/elfio.hpp>

using namespace ELFIO;

void createElf(char *text, char *data){
    elfio writer;
    
    writer.create( ELFCLASS32, ELFDATA2LSB );

    writer.set_os_abi( ELFOSABI_LINUX );
    writer.set_type( ET_EXEC );
    writer.set_machine( EM_386 );

    section* text_sec = writer.sections.add( ".text" );
    text_sec->set_type( SHT_PROGBITS );
    text_sec->set_flags( SHF_ALLOC | SHF_EXECINSTR );
    text_sec->set_addr_align( 0x10 );
    
    text_sec->set_data( text, sizeof( text ) );

    segment* text_seg = writer.segments.add();
    text_seg->set_type( PT_LOAD );
    text_seg->set_virtual_address( 0x08049000 );
    text_seg->set_physical_address( 0x08049000 );
    text_seg->set_flags( PF_X | PF_R );
    text_seg->set_align( 0x1000 );
    
    text_seg->add_section_index( text_sec->get_index(), text_sec->get_addr_align() );

    section* data_sec = writer.sections.add( ".data" );
    data_sec->set_type( SHT_PROGBITS );
    data_sec->set_flags( SHF_ALLOC | SHF_WRITE );
    data_sec->set_addr_align( 0x4 );

    data_sec->set_data( data, sizeof( data ) );

    segment* data_seg = writer.segments.add();
    data_seg->set_type( PT_LOAD );
    data_seg->set_virtual_address( 0x0804a000 );
    data_seg->set_physical_address( 0x0804a000 );
    data_seg->set_flags( PF_W | PF_R );
    data_seg->set_align( 0x1000 );

    data_seg->add_section_index( data_sec->get_index(), data_sec->get_addr_align() );

    section* note_sec = writer.sections.add( ".note" );
    note_sec->set_type( SHT_NOTE );
    note_sec->set_addr_align( 1 );
    note_section_accessor note_writer( writer, note_sec );
    note_writer.add_note( 0x01, "Created by ELFIO", 0, 0 );
    char descr[6] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36};
    note_writer.add_note( 0x01, "Never easier!", descr, sizeof( descr ) );

    writer.set_entry( 0x08049000 );

    writer.save( "hello_i386_32" );
}

int main(int argc, char const *argv[]){
    // std::string filename = argv[1];

    char text[] = { '\xB8', '\x04', '\x00', '\x00', '\x00',   // mov eax, 4		      
                    '\xBB', '\x01', '\x00', '\x00', '\x00',   // mov ebx, 1		      
                    '\xB9', '\x00', '\xa0', '\x04', '\x08',   // mov ecx, msg		      
                    '\xBA', '\x0E', '\x00', '\x00', '\x00',   // mov edx, 14		      
                    '\xCD', '\x80',                           // int 0x80		      
                    '\xB8', '\x01', '\x00', '\x00', '\x00',   // mov eax, 1		      
                    '\xCD', '\x80'};                          // int 0x80

    char data[] = { '\x48', '\x65', '\x6C', '\x6C', '\x6F',   // msg: db   'Hello, World!', 10
                    '\x2C', '\x20', '\x57', '\x6F', '\x72',
                    '\x6C', '\x64', '\x21', '\x0A'};

    createElf(text, data);

    return 0;
}