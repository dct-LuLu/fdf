/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:30:40 by jaubry--          #+#    #+#             */
/*   Updated: 2025/01/22 11:18:38 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <math.h>
#include "portaudio.h"

static int	error(PaError err)
{
	Pa_Terminate();
	ft_dprintf(STDERR_FILENO, "Error number %d\n", err);
	ft_dprintf(STDERR_FILENO, "Error message %s\n", Pa_GetErrorText(err));
	return (err);
}

static void	PrintSupportedStandardSampleRates(
		const PaStreamParameters *inputParameters,
		const PaStreamParameters *outputParameters )
{
	static double	standardSampleRates[] = {
		8000.0, 9600.0, 11025.0, 12000.0, 16000.0, 22050.0, 24000.0, 32000.0,
		44100.0, 48000.0, 88200.0, 96000.0, 192000.0, -1 /* negative terminated  list */
	};
	int				i;
	int				printCount;
	PaError			err;

	printCount = 0;
	i = 0;
	while (standardSampleRates[i] > 0)
	{
		err = Pa_IsFormatSupported(inputParameters, outputParameters, standardSampleRates[i]);
		if (err == paFormatIsSupported)
		{
			if (printCount == 0)
			{
				printf("\t%8.2f", standardSampleRates[i]);
				printCount = 1;
			}
			else if (printCount == 4)
			{
				printf(",\n\t%8.2f", standardSampleRates[i]);
				printCount = 1;
			}
			else
			{
				printf(", %8.2f", standardSampleRates[i]);
				++printCount;
			}
		}
		i++;
	}
	if (!printCount)
		printf("None\n");
	else
		printf("\n");
}

static void	init_pa(void)
{
	PaError	err;

	err = Pa_Initialize();
	if (err != paNoError)
	{
		ft_printf("ERROR: Pa_Initialize returned 0x%x\n", err);
		exit(error(err));
	}
	printf("PortAudio Version: 0x%08X\n", Pa_GetVersion());
	printf("Version text: '%s'\n", Pa_GetVersionInfo()->versionText);
}

void	pa_device_info(void)
{
	const	PaDeviceInfo	*deviceInfo;
	PaStreamParameters		inputParameters;
	PaStreamParameters		outputParameters;
	int						i;
	int						numDevices;
	int						defaultDisplayed;

	init_pa();
	numDevices = Pa_GetDeviceCount();
	if (numDevices < 0)
	{
		printf("ERROR: Pa_GetDeviceCount returned 0x%x\n", numDevices);
		exit(error(numDevices));
	}
	printf("Number of devices = %d\n", numDevices);
	i = 0;
	while (i < numDevices)
	{
		deviceInfo = Pa_GetDeviceInfo(i);
		printf("\n------------------------ device #%d ------------------------\n", i);
		defaultDisplayed = 0;
		if (i == Pa_GetDefaultInputDevice())
		{
			printf("[ Default Input");
			defaultDisplayed = 1;
		}
		else if (i == Pa_GetHostApiInfo(deviceInfo->hostApi)->defaultInputDevice)
		{
			const PaHostApiInfo	*hostInfo = Pa_GetHostApiInfo(deviceInfo->hostApi);
			printf("[ Default %s Input", hostInfo->name);
			defaultDisplayed = 1;
		}
		if (i == Pa_GetDefaultOutputDevice())
		{
			printf((defaultDisplayed ? "," : "["));
			printf(" Default Output");
			defaultDisplayed = 1;
		}
		else if (i == Pa_GetHostApiInfo(deviceInfo->hostApi)->defaultOutputDevice)
		{
			const PaHostApiInfo	*hostInfo = Pa_GetHostApiInfo(deviceInfo->hostApi);
			printf((defaultDisplayed ? "," : "["));
			printf(" Default %s Output", hostInfo->name);
			defaultDisplayed = 1;
		}
		if (defaultDisplayed)
			printf(" ]\n");
		printf("Name                        = %s\n", deviceInfo->name);
		printf("Host API                    = %s\n", Pa_GetHostApiInfo(deviceInfo->hostApi)->name);
		printf("Max inputs = %d", deviceInfo->maxInputChannels);
		printf(", Max outputs = %d\n", deviceInfo->maxOutputChannels);

		printf("Default low input latency   = %8.4f\n", deviceInfo->defaultLowInputLatency);
		printf("Default low output latency  = %8.4f\n", deviceInfo->defaultLowOutputLatency);
		printf("Default high input latency  = %8.4f\n", deviceInfo->defaultHighInputLatency);
		printf("Default high output latency = %8.4f\n", deviceInfo->defaultHighOutputLatency);

		printf( "Default sample rate         = %8.2f\n", deviceInfo->defaultSampleRate);

		inputParameters.device = i;
		inputParameters.channelCount = deviceInfo->maxInputChannels;
		inputParameters.sampleFormat = paInt16;
		inputParameters.suggestedLatency = 0; /* ignored by Pa_IsFormatSupported() */
		inputParameters.hostApiSpecificStreamInfo = NULL;

		outputParameters.device = i;
		outputParameters.channelCount = deviceInfo->maxOutputChannels;
		outputParameters.sampleFormat = paInt16;
		outputParameters.suggestedLatency = 0; /* ignored by Pa_IsFormatSupported() */
		outputParameters.hostApiSpecificStreamInfo = NULL;

		if (inputParameters.channelCount > 0)
		{
			printf("Supported standard sample rates\n for half-duplex 16 bit %d channel input = \n", 
					inputParameters.channelCount);
			PrintSupportedStandardSampleRates(&inputParameters, NULL);
		}

		if (outputParameters.channelCount > 0)
		{
			printf("Supported standard sample rates\n for half-duplex 16 bit %d channel output = \n",
					outputParameters.channelCount);
			PrintSupportedStandardSampleRates(NULL, &outputParameters);
		}

		if (inputParameters.channelCount > 0 && outputParameters.channelCount > 0)
		{
			printf("Supported standard sample rates\n for full-duplex 16 bit %d channel input, %d channel output = \n",
					inputParameters.channelCount, outputParameters.channelCount);
			PrintSupportedStandardSampleRates(&inputParameters, &outputParameters);
		}
		i++;
	}
}

int	main(void)
{
	init_pa();
	pa_device_info();
	Pa_Terminate();
	ft_printf("Execution went well\n");
	return (0);
}
