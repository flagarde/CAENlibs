/******************************************************************************
* 
* CAEN SpA - Computing Division
* Via Vetraia, 11 - 55049 - Viareggio ITALY
* +390594388398 - www.caen.it
*
***************************************************************************//**
* \note TERMS OF USE:
* This program is free software; you can redistribute it and/or modify it under
* the terms of the GNU General Public License as published by the Free Software
* Foundation. This program is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty of 
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. The user relies on the 
* software, documentation and results solely at his own risk.
*
* \file     CAENDigitizerType.h
* \brief    CAEN - Digitizer Library types definition
* \author   Francesco Pepe (support.computing@caen.it)
*
* This library provide functions, structures and definitions for the CAEN
* digitizer family with DPP frirmware
******************************************************************************/

#ifndef __CAENDPPLIBRARY_H
#define __CAENDPPLIBRARY_H

#include <CAENDPPLibTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
- CAENDPP_InitLibrary allows to open a library instance and initialize it
- [OUT] handle  : the handle of the opened DPP library

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_InitLibrary(int32_t * handle);

/*
- CAENDPP_EndLibrary allows to close a specific instance of the DPP Library
- [IN] handle  : the handle of the opened DPP library

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_EndLibrary(int32_t handle);

/*
- CAENDPP_AddBoard allows to open and initialize the connection to a DPP Board
- [IN]  handle     : the handle of the opened DPP instance
- [IN]  connParams : CAENDPP_ConnectionParams_t type structure specifying the connection paramters of the board to add.
- [OUT] boardId    : a numeric value that represent the board opened (used to retrieve boad information)

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_AddBoard(int32_t handle, CAENDPP_ConnectionParams_t connParams, int32_t *boardId);

/*
- CAENDPP_AttachBoards allows to attach to an already running system, whose readout is running on a remote host
- [IN]  IP         : the host IP address where the acquisition is running.
- [IN]  port       : the port on the remote host to use for connection
- [OUT] handle     : the handle to be used with the boards running on the remote instance
- [OUT] numBrd     : the number of boards managed by the server at the connection time
- [OUT] brdIds     : the list of board IDs to be used for boards control, filled up to 'numBrd' valid elements.
                     IMPORTANT: 'brdIds' must be an array of AT LEAST 'MAX_NUMB' elements

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_AttachBoards(char *IP, uint16_t port, int32_t *handle, int32_t *numBrd, int32_t *brdIds);

/*
- CAENDPP_GetDPPInfo allows to know general informations about a specific board

- [IN] handle   : the handle of the opened DPP library
- [IN]  boardId    : the numeric value that represents the board opened
- [OUT] info    : the CAENDPP_Info_t value containing the info about the DPP

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetDPPInfo(int32_t handle, int32_t boardId, CAENDPP_Info_t* info);

/*
- CAENDPP_StartBoardParametersGuess allows to fill Params structure with guessed values
  using an automatic algorithm based on the waveforms acquired from the digitizer.
  This function will start the acquisition for the specified board in Waveforms mode,
  and run the algorithm for the channels specified in channelMask. The algorithm runs
  on a dedicated thread, so that the acquisition for the other boards is not affected.
  Once the user called this method, he must use function 'CAENDPP_GetBoardParametersGuessStatus'
  to monitor the algorthm status and, once the status equals 'CAENDPP_GuessConfigStatus_Ready',
  he must fetch the result using 'CAENDPP_GetBoardParametersGuessResult'. Alternatively,
  he can use the function 'CAENDPP_StopBoardParametersGuess' to stop the algorithm thread
  and ignore the results. See those functions description for details.

- [IN] handle        : the handle of the opened DPP
- [IN] boardId       : the numeric value that represents the board opened
- [IN] channelMask   : mask representing the channels for which guess should be performed
- [IN] Params        : the DgtzParams_t value containing the parameters which must be
                       guessed. The function tries to guess only the parameters
                       initialized to '-1', and assume the others to be provided
                       by the user and uses them whitout changes.

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_StartBoardParametersGuess(int32_t handle, int32_t boardId, uint32_t channelMask, const CAENDPP_DgtzParams_t *Params);

/*
- CAENDPP_GetBoardParametersGuessStatus allows to get the status of the
  algorithm used to guess the acquisition parameters, which can be started
  with function 'CAENDPP_StartBoardParametersGuess'. Once the status
  equals 'CAENDPP_GuessConfigStatus_Ready', he can use function
  'CAENDPP_GetBoardParametersGuessResult' to get the Guess result.

- [IN] handle   : the handle of the opened DPP
- [IN] boardId  : the numeric value that represents the board opened
- [OUT] status  : the status in which the algorithm has been found

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetBoardParametersGuessStatus(int32_t handle, int32_t boardId, CAENDPP_GuessConfigStatus_t *status);

/*
- CAENDPP_GetBoardParametersGuessResult allows to get the resulting
  parameters found from the autoCalibration algorithm, which can be
  started using function 'CAENDPP_StartBoardParametersGuess'. This
  function must be called only when the algortihm status, which can
  be fetched using function 'CAENDPP_GetBoardParametersGuessStatus',
  equals 'CAENDPP_GuessConfigStatus_Ready'. This function also gives
  the channelMask of board's channels for which the autoCalibration
  succeeded. The parameters of the other channels are in an undefined
  state, so the user must manually adjust them before using them to
  set again the board configuration. The user must call this function
  before starting again the acquisition of the board, otherwise the
  board won't acquire new data.

- [IN] handle       : the handle of the opened DPP.
- [IN] boardId      : the numeric value that represents the board
                      opened.
- [OUT] Params      : the DgtzParams_t value containing the parameters
                      found by the algorithm.
- [OUT] succMask    : the channelMask which indicates for which channels
                      the algorithm succeded.

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetBoardParametersGuessResult(int32_t handle, int32_t boardId, CAENDPP_DgtzParams_t *Params, uint32_t *succMask);

/*
- CAENDPP_StopBoardParametersGuess can be used to stop the
  autoCalibration algorithm started with function
  'CAENDPP_StartBoardParametersGuess'. The user must have
  called such function before calling this one, otherwise
  the function will return an error.

- [IN] handle       : the handle of the opened DPP.
- [IN] boardId      : the numeric value that represents the board
                      opened.

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_StopBoardParametersGuess(int32_t handle, int32_t boardId);

/*
- CAENDPP_setBoardConfiguration allows to configure a board
- [IN] handle  : the handle of the opened DPP
- [IN] boardId : the numeric value that represents the board opened
- [IN] acqMode : the acquisition mode to set (Waveforms, Histogram)
- [IN] params  : the set of configuration parameters to write on the board

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_SetBoardConfiguration(int32_t handle, int32_t boardId, CAENDPP_AcqMode_t acqMode, CAENDPP_DgtzParams_t dgtz_params);

/*
- CAENDPP_getBoardConfiguration allows to get the configuration from the specified board.
  The board must be already configured, otherwise the function will return an error.
- [IN]  handle  : the handle of the opened DPP
- [IN]  boardId : the numeric value that represents the board opened
- [OUT] acqMode : the acquisition mode to set (Waveforms, Histogram)
- [OUT] params  : the set of configuration parameters to write on the board

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetBoardConfiguration(int32_t handle, int32_t boardId, CAENDPP_AcqMode_t *acqMode, CAENDPP_DgtzParams_t *dgtz_params);


/*
- CAENDPP_IsChannelEnabled allows to know if a specified channel is enabled

- [IN] handle  : the handle of the opened DPP
- [IN] channel : the number of the channel
- [OUT] enabled: 1 if the channel is enabled, 0 if not

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_IsChannelEnabled(int32_t handle, int32_t channel, int32_t* enabled);

/*
- CAENDPP_IsChannelAcquiring allows to know if the acquisition for a specified channel is ON

- [IN] handle  : the handle of the opened DPP
- [IN] channel : the number of the channel
- [OUT] acquiring: 1 if the channel is enabled, 0 if not

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_IsChannelAcquiring(int32_t handle, int32_t channel, CAENDPP_AcqStatus_t *acquiring);

/*
- CAENDPP_StartAcquisition allows to start the acquisition on the enabled channels of the DPP

- [IN] handle  : the handle of the opened DPP
- [IN] channel : the number of the channel (-1 for all channels)

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_StartAcquisition(int32_t handle, int32_t channel);

/*
- CAENDPP_ArmAcquisition allows to arm the acquisition on the enabled channels of the DPP.
  The acquisition is actually started when an external signal is received.

- [IN] handle  : the handle of the opened DPP
- [IN] channel : the number of the channel (-1 for all channels)

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_ArmAcquisition(int32_t handle, int32_t channel);


/*
- CAENDPP_StopAcquisition allows to stop the acquisition on the enabled channels of the DPP

- [IN] handle  : the handle of the opened DPP
- [IN] channel : the number of the channel (-1 for all channels)

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_StopAcquisition(int32_t handle, int32_t channel);


/*
- CAENDPP_IsBoardAcquiring allows to know the acquisition status

- [IN] handle       : the handle of the opened DPP
- [OUT] isAcquiring : 1 if the DPP is acquiring, 0 if not

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_IsBoardAcquiring(int32_t handle, int32_t boardId, int32_t* isAcquiring);


/*
- CAENDPP_SetHistoSwitchMode allows to switch the histogram when a specified condition is verified.

- [IN] handle       : the handle of the opened DPP
- [IN] condition    : the condition for which to change histogram

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_SetHistoSwitchMode(int32_t handle, CAENDPP_MultiHistoCondition_t condition);

/*
- CAENDPP_GetHistoSwitchMode allows to know the condition that switch the histogram.

- [IN] handle       : the handle of the opened DPP
- [OUT] condition    : the condition for which to change histogram

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetHistoSwitchMode(int32_t handle, CAENDPP_MultiHistoCondition_t *condition);

/*
- CAENDPP_SetStopCriteria allows to set the condition that stops the acquisition.

- [IN] handle       : the handle of the opened DPP
- [IN] channel         : the number of the channel, -1 to set all channels
- [IN] stopCrit        : the condition for which to change histogram
- [IN] value        : the value in nanoseconds/counts after which the Acquisition is Stopped.

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_SetStopCriteria(int32_t handle, int32_t channel, CAENDPP_StopCriteria_t stopCrit, uint64_t value);

/*
- CAENDPP_GetStopCriteria allows to get the condition that stops the acquisition.

- [IN]  handle      : the handle of the opened DPP
- [IN]  channel     : the number of the channel, -1 to set all channels
- [OUT] stopCrit    : the condition for which to change histogram
- [OUT] value        : the value in nanoseconds/counts after which the Acquisition is Stopped.

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetStopCriteria(int32_t handle, int32_t channel, CAENDPP_StopCriteria_t *stopCrit, uint64_t *value);

/*
- CAENDPP_GetTotalNumberOfHistograms allows to know the total number of histograms (completed or not)

- [IN] handle       : the handle of the opened DPP
- [IN] channel         : the number of the channel, -1 to read from all the channels
- [IN] numHisto         : the number of histogram available. A preallocated array of int32_t must be supplied in case channel == -1.

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetTotalNumberOfHistograms(int32_t handle, int32_t channel, int32_t *numHisto);

/*
- CAENDPP_GetNumberOfCompletedHistograms allows to know the number of completed histograms

- [IN] handle       : the handle of the opened DPP
- [IN] channel         : the number of the channel, -1 to read from all the channels
- [IN] numHisto         : the number of histogram available. A preallocated array of int32_t must be supplied in case channel == -1.

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetNumberOfCompletedHistograms(int32_t handle, int32_t channel, int32_t *numHisto);

/*
- CAENDPP_GetListEvents allows to get list events from the board up to MAX_LIST_BUFF_NEV events for the specified channel

- [IN]  handle        : the handle of the opened DPP
- [IN]  channel        : the number of the channel, -1 to read from all the channels
- [OUT] listEvents  : pointer to the list event structure. See CAENDPP_ListEvent_t for description
- [OUT] nEvts        : number of events in the structure
*/
int32_t CAENDPP_API CAENDPP_GetListEvents(int32_t handle, int32_t channel, CAENDPP_ListEvent_t *listEvents, uint32_t *nEvts);

/*
- CAENDPP_GetWaveform allows to get the first waveform red in the next readout.
If no wave is received in the next readout for the specified channel, the number of sanples is 0

- [IN]  handle          : the handle of the opened DPP
- [IN]  channel         : the number of the channel
- [IN]  AUTO            : if set to '1', emulates the 'AUTO' trigger mode of a common oscilloscope.
- [OUT] analogTrace1    : a pointer to the first analog trace samples values.
- [OUT] analogTrace2    : a pointer to the second analog trace samples values.
- [OUT] digitalTrace1   : a pointer to the first digital trace samples values.
- [OUT] digitalTrace2   : a pointer to the second digital trace samples values.
- [OUT] ns              : the number of samples for that wave. If no wave is read for that channel, ns = 0;
- [OUT] tsample         : the value in nanoseconds of a single sample
*/
int32_t CAENDPP_API CAENDPP_GetWaveform(int32_t handle, int32_t channel, int16_t AUTO, int16_t *analogTrace1, int16_t *analogTrace2, uint8_t *digitalTrace1, uint8_t *digitalTrace2, uint32_t *ns, double *tsample);

/*
- CAENDPP_GetHistogram allows to get an histogram from memory, this function doesn't erase the histogram's data.

- [IN] handle       : the handle of the opened DPP
- [IN] channel         : the number of the channel
- [IN] histoIndex    : the index of the stored histogram to get 
                    (the most recent histogram has the index of available spectra - 1)
- [OUT] histo        : the requested histogram        
- [OUT] counts        : the number of counts in the histogram
- [OUT] realTime_ns    : the real time expressed in nanoseconds of the histogram
- [OUT] deadTime_ns    : the dead time expressed in nanoseconds of the histogram                    

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetHistogram(int32_t handle, int32_t channel, int32_t histoIndex, void *histo, uint32_t *counts, uint64_t *realTime_ns, uint64_t *deadTime_ns);

/*
- CAENDPP_SetHistogram allows to store an histogram at index histoIndex for the specified channel.
  This function erases any previously acquired data for that histogram.

- [IN] handle       : the handle of the opened DPP
- [IN] channel         : the number of the channel
- [IN] histoIndex    : the index of the histogram to store
                    (the most recent histogram has the index of available spectra - 1)
- [IN] histo        : the histogram    to store
- [IN] nbins        : the number of bins in the histogram
- [IN] realTime_ns    : the real time expressed in nanoseconds of the histogram
- [IN] deadTime_ns    : the dead time expressed in nanoseconds of the histogram                    

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_SetHistogram(int32_t handle, int32_t channel, int32_t histoIndex, uint64_t realTime_ns, uint64_t deadTime_ns, uint32_t nbins, uint32_t *histo);

/*
- CAENDPP_GetCurrentHistogram allows to get the active histogram from memory and the status of
  the Acquisition for the specified channel. This function doesn't erase the histogram's data.

- [IN] handle       : the handle of the opened DPP
- [IN] channel         : the number of the channel
- [OUT] histo        : the requested histogram        
- [OUT] counts        : the number of counts in the histogram
- [OUT] realTime_ns    : the real time expressed in nanoseconds of the histogram
- [OUT] deadTime_ns    : the dead time expressed in nanoseconds of the histogram                    
- [OUT] AcqStatus    : the Acquisition Status of the specified channel.
- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetCurrentHistogram(int32_t handle, int32_t channel, void *histo, uint32_t *counts, uint64_t *realTime_ns, uint64_t *deadTime_ns, CAENDPP_AcqStatus_t *acqStatus);

/*
- CAENDPP_SaveHistogram allows to save the histogram at index histoIndex for the specified channel to disk.

- [IN] handle       : the handle of the opened DPP
- [IN] channel         : the number of the channel
- [IN] histoIndex    : the index of the histogram to store
                    (the most recent histogram has the index of available spectra - 1)
- [IN] filename        : the name of the file which will contain histogram data.

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_SaveHistogram(int32_t handle, int32_t channel, int32_t histoIndex, char *filename);

/*
- CAENDPP_LoadHistogram allows to load the histogram at index histoIndex for the specified channel from disk.
  This function erases any previously acquired data for that histogram.

- [IN] handle       : the handle of the opened DPP
- [IN] channel         : the number of the channel
- [IN] histoIndex    : the index of the histogram to load from disk
                    (the most recent histogram has the index of available spectra - 1)
- [IN] filename        : the name of the file which contains histogram data to load.

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_LoadHistogram(int32_t handle, int32_t channel, int32_t histoIndex, char *filename);

/*
- CAENDPP_ClearHistogram allows to clear data of a specified histogram.

- [IN] handle       : the handle of the opened DPP
- [IN] channel         : the number of the channel
- [IN] histoIndex    : the index of the stored histogram to clear
                    (the most recent histogram has the index of available spectra - 1)

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_ClearHistogram(int32_t handle, int32_t channel, int32_t histoIndex);

/*
- CAENDPP_ClearCurrentHistogram allows to clear data of the current histogram.

- [IN] handle       : the handle of the opened DPP
- [IN] channel         : the number of the channel

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_ClearCurrentHistogram(int32_t handle, int32_t channel);


/*
- CAENDPP_ClearAllHistograms allows to clear data of all histograms of the given channel.
  NOTE: if some histograms of the given channel are in 'completed' state, this function
  will return the error 'CAENDPP_RetCode_BadHistoState', and the corresponding histogram
  will not be cleared. Manage the error outside the library if you want to ignore it.

- [IN] handle       : the handle of the opened DPP
- [IN] channel      : the number of the channel. if 'channel == -1' clears the histograms
                      of all channels.

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_ClearAllHistograms(int32_t handle, int32_t channel);

/*
- CAENDPP_ResetHistogram allows to reset the histogram at the given index. The datas are
  cleared and the completed flag is set to false

- [IN] handle       : the handle of the opened DPP
- [IN] channel      : the number of the channel
- [IN] histoIndex   : the index of the stored histogram to reset

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_ResetHistogram(int32_t handle, int32_t channel, int32_t histoIndex);

/*
- CAENDPP_ResetAllHistograms allows to reset all the histograms of a given channel.

- [IN] handle       : the handle of the opened DPP
- [IN] channel      : the number of the channel. If channel == -1 resets the
                      histogram of all available channels.

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_ResetAllHistograms(int32_t handle, int32_t channel);

/*
- CAENDPP_ForceNewHistogram allows to force the creation of a new histogram for a given channel

- [IN] handle       : the handle of the opened DPP
- [IN] channel      : the number of the channel

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_ForceNewHistogram(int32_t handle, int32_t channel);

/*
- CAENDPP_SetHistogramSize allows to set the size in bins of the histogram at the given index
- [IN] handle       : the handle of the opened DPP
- [IN] channel      : the number of the channel
- [IN] histoIndex   : the index of the stored histogram to set. If the given index is
                      equal to the number of added histograms, a new histogram is created.
- [IN] size         : the histogram size in bins. Must be a power of 2 until up 16384.

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_SetHistogramSize(int32_t handle, int32_t channel, int32_t histoIndex, int32_t size);

/*
- CAENDPP_GetHistogramSize allows to get the size in bins of the histogram at the given index
- [IN] handle       : the handle of the opened DPP
- [IN] channel      : the number of the channel
- [IN] histoIndex   : the index of the stored histogram to get the size.
- [OUT] size         : the histogram size in bins.

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetHistogramSize(int32_t handle, int32_t channel, int32_t histoIndex, int32_t *size);

/*
- CAENDPP_AddHistogram allows to add a new histogram of the given size
- [IN] handle       : the handle of the opened DPP
- [IN] channel      : the number of the channel
- [IN] size         : the histogram size in bins. Must be a power of 2 until up 16384.

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_AddHistogram(int32_t handle, int32_t channel, int32_t size);

/*
- CAENDPP_SetCurrentHistogramIndex allows to select the current histogram from
  its index. The selected histogram must not be already completed. If you want
  to set an already completed histogram as active, call CAENDPP_Reset_Histogram
  or CAENDPP_SetHistogramComplete to false on it before.

- [IN] handle       : the handle of the opened DPP
- [IN] channel      : the number of the channel
- [IN] histoIndex   : the index of the stored histogram to select

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_SetCurrentHistogramIndex(int32_t handle, int32_t channel, int32_t histoIndex);

/*
- CAENDPP_GetCurrentHistogramIndex allows to get the current histogram index.

- [IN] handle       : the handle of the opened DPP
- [IN] channel      : the number of the channel
- [OUT] histoIndex  : the index of the stored histogram to select. -1 Means that
                      no histogram is currently active, other negative values means
                      that an error occurred.

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetCurrentHistogramIndex(int32_t handle, int32_t channel, int32_t *histoIndex);

/*
- CAENDPP_SetHistogramCompleted allows to set if an histogram is completed or
  not. The selected index cannot be the one of the current histogram.

- [IN] handle       : the handle of the opened DPP
- [IN] channel      : the number of the channel
- [IN] histoIndex   : the index of the stored histogram to select
- [IN] completed    : the value of the completed flag

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_SetHistogramStatus(int32_t handle, int32_t channel, int32_t histoIndex, int32_t completed);

/*
- CAENDPP_GetHistogramCompleted allows to get if an histogram is completed or
  not.

- [IN] handle       : the handle of the opened DPP
- [IN] channel      : the number of the channel
- [IN] histoIndex   : the index of the stored histogram to select
- [OUT] completed   : the value of the completed flag

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetHistogramStatus(int32_t handle, int32_t channel, int32_t histoIndex, int32_t *completed);

/*
- CAENDPP_SetHistogramRange allows to set the interesting range of a channel's histograms

- [IN] handle       : the handle of the opened DPP library
- [IN] channel        : the number of the channel
- [IN] lower        : the Lower Level Discriminator
- [IN] upper        : the Upper Level Discriminator

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_SetHistogramRange(int32_t handle, int32_t channel, int32_t lower, int32_t upper);

/*
- CAENDPP_GetHistogramRange allows to get the interesting range of a channel's histograms

- [IN] handle       : the handle of the opened DPP library
- [IN] channel        : the number of the channel
- [OUT] lower       : the Lower Level Discriminator
- [OUT] upper       : the Upper Level Discriminator

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetHistogramRange(int32_t handle, int32_t channel, int32_t* lower, int32_t* upper);

/*
- CAENDPP_EnableSwTriggers allows to enable the software trigger

- [IN] handle       : the handle of the opened DPP library

- return : 0 for success otherwise an error code.
*/
DPP_DEPRECATED(int32_t CAENDPP_API CAENDPP_EnableSwTriggers(int32_t handle));

/*
- CAENDPP_DisableSwTriggers allows to disable the software trigger

- [IN] handle       : the handle of the opened DPP library

- return : 0 for success otherwise an error code.
*/
DPP_DEPRECATED(int32_t CAENDPP_API CAENDPP_DisableSwTriggers(int32_t handle));

/*
- CAENDPP_GetAcqStats allows to get the statistics of the acquisition for a specified channel

- [IN] handle       : the handle of the opened DPP library
- [IN] channel        : the number of the channel
- [OUT] stats       : the statistic of the specified channel

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetAcqStats(int32_t handle, int32_t channel, statistics_t* stats);

/*
- CAENDPP_SetInputRange allows to set the Input Level of the given channel
- [IN] handle       : the handle of the opened DPP library
- [IN] channel      : the number of the channel
- [IN] iputLevel    : the input level

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_SetInputRange(int32_t handle, int32_t channel, CAENDPP_InputRange_t iputLevel);

/*
- CAENDPP_GetWaveformLength allows to get the statistics of the acquisition for a specified channel

- [IN] handle       : the handle of the opened DPP library
- [IN] channel      : the number of the channel
- [OUT] iputLevel      : the input level

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetInputRange(int32_t handle, int32_t channel, CAENDPP_InputRange_t *iputLevel);

/*
- CAENDPP_GetWaveformLength allows to get the length in samples of the waveform for a specified channel

- [IN] handle       : the handle of the opened DPP library
- [IN] channel      : the number of the channel
- [OUT] length      : the length of the waveform in samples

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetWaveformLength(int32_t handle, int32_t channel, uint32_t* length);

/*
- CAENDPP_CheckBoardCommunication allows to know if the communication with
  the given board is ok.
- [IN] handle   : the handle of the opened DPP library
- [IN] boardId    : the number of the board

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_CheckBoardCommunication(int32_t handle, int32_t boardId);

/*
- CAENDPP_GetParameterInfo allows to get the given parameters information for the
  given channel, basing on its current configuration.
- [IN] handle   : the handle of the opened DPP library.
- [IN] ch       : the number of the channel.
- [IN] param    : the parameter to know the info for.
- [OUT] info    : the informations requested.

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetParameterInfo(int32_t handle, int32_t ch, CAENDPP_ParamID_t param, CAENDPP_ParamInfo_t *info);

/*
- CAENDPP_BoardADCCalibration allows to calibrate board's ADCs
- [IN] handle   : the handle of the opened DPP library.
- [IN] brd      : the board index.

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_BoardADCCalibration(int32_t handle, int32_t brd);

/*
- CAENDPP_GetChannelTemperature allows to get the temperature of the
  given channel
- [IN] handle   : the handle of the opened DPP library.
- [IN] channel  : the channel index.
- [OUT] temp    : the read temperature

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetChannelTemperature(int32_t handle, int32_t channel, double *temp);

/*
- CAENDPP_GetDAQInfo allows to get the DAQ informations for the
  given channel
- [IN] handle   : the handle of the opened DPP library.
- [IN] channel  : the channel index.
- [OUT] infos   : the DAQ informations.

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetDAQInfo(int32_t handle, int32_t channel, CAENDPP_DAQInfo_t *infos);

/*
- CAENDPP_ResetConfiguration allows to reset the board configuration to default.
- [IN] handle   : the handle of the opened DPP library
- [IN] boardId    : the number of the board

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_ResetConfiguration(int32_t handle, int32_t boardId);

/*
- CAENDPP_SetHVChannelConfiguration allows to set the configuration of an HV channel
  NOTE: this function does not set VMax, for this there is a dedicated function

- [IN] handle    : the handle of the opened DPP library
- [IN] bId        : the numeric value that represents the board opened
- [IN] ch        : the number of the channel
- [IN] config    : the configuration to set for the specified HV channel

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_SetHVChannelConfiguration(int32_t handle, int32_t bId, int32_t ch, CAENDPP_HVChannelConfig_t config);

/*
- CAENDPP_GetHVChannelConfiguration allows to get the current configuration of an HV channel

- [IN] handle    : the handle of the opened DPP library
- [IN] bId        : the numeric value that represents the board opened
- [IN] ch        : the number of the channel
- [OUT] config    : the configuration to set for the specified HV channel

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetHVChannelConfiguration(int32_t handle, int32_t bId, int32_t ch, CAENDPP_HVChannelConfig_t *config);

/*
- CAENDPP_SetHVChannelVMax allows to set the VMax of an HV channel

- [IN] handle    : the handle of the opened DPP library
- [IN] bId        : the numeric value that represents the board opened
- [IN] ch        : the number of the channel
- [IN] VMax        : the configuration to set for the specified HV channel

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_SetHVChannelVMax(int32_t handle, int32_t bId, int32_t ch, double VMax);

/*
- CAENDPP_GetHVChannelConfiguration allows to get the current status of an HV channel

- [IN] handle    : the handle of the opened DPP library
- [IN] bId        : the numeric value that represents the board opened
- [IN] ch        : the number of the channel
- [OUT] status    : the encoded status of the specified HV channel

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetHVChannelStatus(int32_t handle, int32_t bId, int32_t ch, uint16_t *status);

/*
- CAENDPP_SetHVChannelPowerOn allows to switch on/off an HV channel

- [IN] handle    : the handle of the opened DPP library
- [IN] bId        : the numeric value that represents the board opened
- [IN] ch        : the number of the channel
- [IN] on        : 0 = switch off, 1 = switch on

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_SetHVChannelPowerOn(int32_t handle, int32_t bId, int32_t ch, int32_t on);

/*
- CAENDPP_GetHVChannelPowerOn allows to get wether an HV channel is switched on/off

- [IN] handle    : the handle of the opened DPP library
- [IN] bId        : the numeric value that represents the board opened
- [IN] ch        : the number of the channel
- [OUT] on        : 0 = channel switched off, 1 = channel switched on

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetHVChannelPowerOn(int32_t handle, int32_t bId, int32_t ch, uint32_t *on);

/*
- CAENDPP_ReadHVChannelMonitoring allows to get the monitored tension (VMon (V))
  and current (IMon (uA)) of the specified channel

WARNING: This function may take up to 10 ms to be executed

- [IN] handle    : the handle of the opened DPP library
- [IN] bId        : the numeric value that represents the board opened
- [IN] ch        : the number of the channel
- [OUT] VMon    : The value of the monitored tension (V)
- [OUT] IMon    : The value of the monitored current (uA)

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_ReadHVChannelMonitoring(int32_t handle, int32_t bId, int32_t ch, double *VMon, double *IMon);

/*
- CAENDPP_ReadHVChannelExternals allows to get the monitored tension (VExt (V))
  and PT100 (TRes (Ohm)) of the specified channel

WARNING: This function may take up to 10 ms to be executed

- [IN] handle    : the handle of the opened DPP library
- [IN] bId        : the numeric value that represents the board opened
- [IN] ch        : the number of the channel
- [OUT] VExt    : The value of the monitored tension (V)
- [OUT] TRes    : The value of the monitored current (Ohm)

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_ReadHVChannelExternals(int32_t handle, int32_t bId, int32_t ch, double *VExt, double *TRes);

/*
- CAENDPP_EnumerateDevices searches for devices physically connected
  and returns their informations

- [IN] handle       : the handle of the opened DPP library
- [OUT] DeviceList  : The list of found devices

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_EnumerateDevices(int32_t handle, CAENDPP_EnumeratedDevices_t* DeviceList);

/*
- CAENDPP_GetHVStatusString allows to convert the encoded channel status to a Human Readable string

- [IN] status        : the encoded status
- [OUT] statusString: the Human Readable string

- return : 0 for success otherwise an error code.
*/
int32_t CAENDPP_API CAENDPP_GetHVStatusString(int32_t handle, int32_t bId, uint16_t status, char *statusString);


#ifdef __cplusplus
}
#endif

#endif