/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signature.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:20:16 by xxxxxxx           #+#    #+#             */
/*   Updated: 2026/02/11 17:09:43 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pestilence.h"

void signature(char str[])
{
	__asm__(".intel_syntax noprefix;"
			"lea rsi, [rip+sign_data]\n"
			"mov rdx, 43\n"
			"call memcpy\n"
			"jmp end_sign\n"
			"sign_data: .ascii \"\nPestilence v1.0 (c)oded by "
			"xxxxxxx - yyyyyy\n\"\n"
			"end_sign:\n"
			:
			: "rdi"(str)
			: "rdi", "rsi", "rdx", "rax");
}
