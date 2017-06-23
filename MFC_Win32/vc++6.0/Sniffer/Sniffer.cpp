// Sniffer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <pcap.h>
#pragma comment(lib,"wpcap.lib")

/* 4�ֽ�IP��ַ*/
typedef struct ip_address
{
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
} ip_address;

/*
// IP��������ʾ����μ�RFC791
0 1 2 3
����������

*/
/* IPv4 ͷ */
typedef struct ip_header
{
	u_char ver_ihl; // 4λ�ײ����ȣ�4λIP�汾��
	u_char tos; // 8λ��������TOS
	u_short tlen; // 16λ�ܳ��ȣ��ֽڣ�
	u_short	identification; // 16λ��ʶ
	u_short flags_fo; // 3λ��־λ��13λƫ��
	u_char ttl; // 8λ����ʱ��TTL
	u_char proto; // 8λЭ�飨TCP��UDP��������
	u_short crc; // 16λIP�ײ�У���
	ip_address saddr; // 32λԴIP��ַ
	ip_address daddr; // 32λĿ��IP��ַ
	u_int op_pad; // 32λѡ��
}ip_header;

/*
// TCP�����¸�ʽ��
��������������������
����������
��������������

*/
// ����TCP�ײ�
typedef struct tcp_header
{
	u_short sport; // 16λԴ�˿�
	u_short dport; // 16λĿ�Ķ˿�
	u_int seq; // 32λ���к�
	u_int ack; // 32λȷ�Ϻ�
	u_char lenres; // 4λ�ײ����� / 6λ������
	u_char flag; // 6λ��־λ
	u_short win; // 16λ���ڴ�С
	u_short sum; // 16λУ���
	u_short urp; // 16λ��������ƫ����
	u_int op_pad; // 32λѡ��
}tcp_header;

/*
// UDP ��������ʾ
��������������
��������
����������������
������������
������
*/
/* UDP header */
typedef struct udp_header
{
	u_short sport; // 16λԴ�˿�
	u_short dport; // 16λĿ�Ķ˿�
	u_short len; // 16λ����
	u_short crc; // 16λУ���
}udp_header;

// sniffer.c �������̨Ӧ�ó������ڵ㡣
int main(int argc, char* argv[])
{
	pcap_if_t* alldevs;
	pcap_if_t* d;
	int inum;
	int i = 0;
	pcap_t* fp;
	char* ofilename = "sniffer.txt";
	char errbuf[PCAP_ERRBUF_SIZE];
	u_int netmask;
	int res;
	struct pcap_pkthdr *header;
	const u_char * pkt_data;
	char packet_filter[] = "ip and tcp and udp";
	pcap_dumper_t *dumpfile;
	struct bpf_program fcode;
	ip_header * ih;
	tcp_header* th;
	udp_header * uh;
	u_int ip_len;
	u_short sport,dport;

	// ��������豸ָ��
	if( pcap_findalldevs_ex( PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf ) == -1 )
	{
		fprintf( stderr, "pcap_findalldevs ���� %s \n", errbuf );
		exit(1);
	}
	// ö��������Ϣ
	for ( d = alldevs; d; d = d->next )
	{
		printf( "%d. %s", ++i, d->name );
		if( d->description )
		{
			printf( " (%s) \n", d->description );
		}
		else
		{
			printf( "(��������Ϣ)\n");
		}
	}
	if( i == 0 )
	{
		printf("\nû�����κνӿڣ���ȷ���Ƿ��Ѿ���װWinPcap��. \n" );
		return -1;
	}
	printf( "�����������ӿںţ�1 - %d��:", i);
	scanf( "%d", &inum );
	if( inum < 1 || inum > i )
	{
		printf( "\n�ӿںų�����Χ��\n");
		// �ͷ�alldevs��Դ
		pcap_freealldevs(alldevs);
		return -1;
	}
	// ����ѡ�������
	for( d = alldevs, i = 0; i < inum - 1; d = d->next, i++ );
	// ������
	if( ( fp = pcap_open( d->name, // �豸����
		65536,
		PCAP_OPENFLAG_PROMISCUOUS, // ����ģʽ
		1000, // ��ȡ��ʱʱ��
		NULL, // Զ����֤�����������Ǳ�����̽������Ҫ����
		errbuf )) == NULL )
	{
		fprintf( stderr, "\nUnable to open the adapter. %s is not supported by Winpcap \n " );
		// �ͷ���Դ
		pcap_freealldevs(alldevs);
		return -1;
	}
	// �����·�㣬������ֻ�򵥵�֧����̫��
	if( pcap_datalink(fp) != DLT_EN10MB )
	{
		fprintf( stderr, "\n������ֻ�򵥵�֧����̫����\n");
		// �ͷ���Դ
		pcap_freealldevs(alldevs);
		return -1;
	}
	if( d->addresses != NULL )
	{
		// ȡ��һ������ӿڵ���������
		netmask = ( (struct sockaddr_in *) ( d->addresses->netmask ))->sin_addr.S_un.S_addr;
	}
	else
	{
		netmask = 0xffffffff;
	}
	// �༭������
	if( pcap_compile( fp, &fcode, packet_filter, 1, netmask ) < 0 )
	{
		fprintf( stderr, "\n���ܱ�������ˣ�����������ʽ\n");
		// �ͷ���Դ
		pcap_freealldevs(alldevs);
		return -1;
	}
	// ���ù�����
	if( pcap_setfiler( fp, &fcode ) < 0 )
	{
		fprintf( stderr,"\n���ù�����ʧ��\n");
		// �ͷ���Դ
		pcap_freealldevs(alldevs);
		return -1;
	}
	printf( "nlistening on %s ... \n", d->description );
	// �ͷ�alldevs��Դ����Ϊ������Ҫ��
	pcap_freealldevs(alldevs);
	// ������ļ�
	dumpfile = pcap_dump_open( fp, ofilename );
	if( dumpfile == NULL )
	{
		fprintf( stderr, "\n������ļ�����\n");
		pcap_close(fp);
		return -1;
	}
	// ��ʼ�������ݰ�
	while ( ( res = pcap_next_ex( fp, &header, &pkt_data )) > 0 )
	{
		if( res == 0 ) /* ��ʱ���� */
		{
			continue;
		}
		// ����������ݰ������ļ�
		pcap_dump( (unsigned char *) dumpfile, header, pkt_data );
		// ȡ��IPͷ��14Ϊ��̫��ͷ����
		ih = (ip_header*)( pkt_data + 14 );
		ip_len = ( ih->ver_ihl & 0xf ) * 4;
		if( ih->proto == 6 ) // TCP
		{
			// ȡTCPͷ
			th = (tcp_header*)( (u_char*)ih + ip_len );
			/* convert from network byte order to host byte order */
			sport = ntohs( th->sport ); // �����ֽ���ת�����ֽ���
			dport = ntohs( th->dport ); // ͬ��
			/* ��ӡIP��ַ�Ͷ˿ں� */
			printf( "%d.%d.%d.%d:%d-> %d.%d.%d.%d:%d\n",
				ih->saddr.byte1,
				ih->saddr.byte2,
				ih->saddr.byte3,
				ih->saddr.byte4,
				sport,
				ih->daddr.byte1,
				ih->daddr.byte2,
				ih->daddr.byte3,
				ih->daddr.byte4,
				dport);
		}
		else if ( ih->proto == 17 ) // UDP
		{
			// ȡUDPͷ
			uh = (udp_header*)( ( u_char*)ih + ip_len );
			/* convert from network byte order to host byte order */
			sport = ntohs( uh->sport ); // �����ֽ���ת�����ֽ���
			dport = ntohs( uh->dport ); // �����ֽ���ת�����ֽ���
			printf ( "%d.%d.%d.%d:%d-> %d.%d.%d.%d:%d\n",
				ih->saddr.byte1,
				ih->saddr.byte2,
				ih->saddr.byte3,
				ih->saddr.byte4,
				sport,
				ih->daddr.byte1,
				ih->daddr.byte2,
				ih->daddr.byte3,
				ih->daddr.byte4,
				dport);
		}
	}
	pcap_close(fp);
	pcap_dump_close(dumpfile);
	return 0;
}
