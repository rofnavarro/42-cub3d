/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rferrero <rofnavarro@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 20:25:51 by rferrero          #+#    #+#             */
/*   Updated: 2021/11/15 00:42:43 by rferrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *s, char c)
{
	int	counter;
	int	word_counter;

	counter = 0;
	word_counter = 0;
	while (s[counter] != '\0')
	{
		if (s[counter] == c)
		{
			counter++;
		}
		else
		{
			word_counter++;
			while (s[counter] && s[counter] != c)
			{
				counter++;
			}
		}
	}
	return (word_counter);
}

static char	*ft_make_word(char *word, char const *s,
							int cut_pos, int word_length)
{
	int	counter;

	counter = 0;
	while (word_length > 0)
	{
		word[counter] = s[cut_pos - word_length];
		counter++;
		word_length--;
	}
	word[counter] = '\0';
	return (word);
}

static char	**ft_real_split(char **word, char const *s, char c,
								int number_of_words)
{
	int	word_counter;
	int	counter;
	int	word_length;

	word_counter = 0;
	counter = 0;
	word_length = 0;
	while (s[counter] && word_counter < number_of_words)
	{
		while (s[counter] && s[counter] == c)
		{
			counter++;
		}
		while (s[counter] && s[counter] != c)
		{
			counter++;
			word_length++;
		}
		word[word_counter] = (char *)malloc (sizeof(char) * (word_length + 1));
		ft_make_word(word[word_counter], s, counter, word_length);
		word_length = 0;
		word_counter++;
	}
	word[word_counter] = NULL;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**word;
	int		number_of_words;

	number_of_words = ft_word_count(s, c);
	word = (char **)malloc (sizeof(char *) * (number_of_words + 1));
	ft_real_split(word, s, c, number_of_words);
	return (word);
}
